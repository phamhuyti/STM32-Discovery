#include "RFID.h"
// See page 25 of the L3GD20 datasheet for details on how we send commands to, and make
// queries of, the gyro.  If you look at figure 14 of UM1842 on page 33 you'll see how
// the L3GD20 pins are connected to the STM32F411:
//    CS  --> PE2   // Chip Select
//    SPC --> PA5   // Clock
//    SDI --> PA7   // Data In
//    SDO --> PA6   // Data Out
// As shown on page 25 of the L3GD20 communication with the gyro takes the following steps:
// 1) The chip select must go from high to low to indicate we're doing a read or write.
// 2) The first byte we send is the register of the gyro (combined with 0x80 if we're going
//    to do a read operation).
// 3) Do a read from SDO
// 4) Write the next byte
// 5) Read a result
// 6) Set CS back to high
/////////////////////////////////////////////////////////////////////////////////////
// Basic interface functions for communicating with the MFRC522
/////////////////////////////////////////////////////////////////////////////////////
/**
 * Sets the bits given in mask in register reg.
 */

// Member variables
TagInfo tag;
void PCD_WriteRegister(enum	PCD_Register reg, unsigned char value){
	ACCESS(GPIOE_BSRR) |= (1 << 18);
	WaitForSPI1TXReady();
	ACCESS(SPI1_DR) = reg;
	WaitForSPI1RXReady();
	ACCESS(SPI1_DR);  // I believe we need this simply because a read must follow a write
	WaitForSPI1TXReady();
	ACCESS(SPI1_DR) = value;
	WaitForSPI1RXReady();
	ACCESS(SPI1_DR);  // Don't care what valley the device put into the data register
	ACCESS(GPIOE_BSRR) |= (1 << 2);
}
/**
 * Writes a number of bytes to the specified register in the MFRC522 chip.
 * The interface is described in the datasheet section 8.1.2.
 */
void PCD_WriteRegister_3(enum	PCD_Register reg,	///< The register to write to. One of the PCD_Register enums.
						byte count,			///< The number of bytes to write to the register
						byte *values		///< The values to write. Byte array.
						) {
	ACCESS(GPIOE_BSRR) |= (1 << 18);
	WaitForSPI1TXReady();
	ACCESS(SPI1_DR) = reg;					// MSB == 0 is for writing. LSB is not used in address. Datasheet section 8.1.2.3.
	for (byte index = 0; index < count; index++) {
		WaitForSPI1TXReady();
		ACCESS(SPI1_DR) = values[index];
	}
	WaitForSPI1RXReady();
	ACCESS(SPI1_DR);  // Don't care what valley the device put into the data register
	ACCESS(GPIOE_BSRR) |= (1 << 2);
} // End PCD_WriteRegister()
unsigned char PCD_ReadRegister(unsigned char RegisterRFID){
	ACCESS(GPIOE_BSRR) |= (1 << 18);
	WaitForSPI1TXReady();
	ACCESS(SPI1_DR) = (RegisterRFID); // 0x80 indicates we're doing a read
	WaitForSPI1RXReady();
	ACCESS(SPI1_DR);  // I believe we need this simply because a read must follow a write
	WaitForSPI1TXReady();
	ACCESS(SPI1_DR) = 0xFF;
	WaitForSPI1RXReady();
	volatile unsigned char readValue = (unsigned char)ACCESS(SPI1_DR);
	ACCESS(GPIOE_BSRR) |= (1 << 2);

	return readValue;
}
/**
 * Reads a number of bytes from the specified register in the MFRC522 chip.
 * The interface is described in the datasheet section 8.1.2.
 */
void PCD_ReadRegister_3(enum	PCD_Register reg,	///< The register to read from. One of the PCD_Register enums.
								byte count,			///< The number of bytes to read
								byte *values,		///< Byte array to store the values in.
								byte rxAlign		///< Only bit positions rxAlign..7 in values[0] are updated.
								) {
	if (count == 0) {
		return;
	}
	//Serial.print(F("Reading ")); 	Serial.print(count); Serial.println(F(" bytes from register."));
	byte address = reg;				// MSB == 1 is for reading. LSB is not used in address. Datasheet section 8.1.2.3.
	byte index = 0;							// Index in values array.
	ACCESS(GPIOE_BSRR) |= (1 << 18);		// Select slave
	count--;								// One read is performed outside of the loop
	ACCESS(SPI1_DR) = (address);				// Tell MFRC522 which address we want to read
	WaitForSPI1RXReady();
	if (rxAlign) {		// Only update bit positions rxAlign..7 in values[0]
		// Create bit mask for bit positions rxAlign..7
		byte mask = (0xFF << rxAlign) & 0xFF;
		// Read value and tell that we want to read the same address again.
		ACCESS(SPI1_DR) = address;
		WaitForSPI1RXReady();
		volatile unsigned char value = (unsigned char)ACCESS(SPI1_DR);
		WaitForSPI1TXReady();
		// Apply mask to both current value of values[0] and the new data in value.
		values[0] = (values[0] & ~mask) | (value & mask);
		index++;
	}
	while (index < count) {
		values[index] = ACCESS(SPI1_DR) = (address);	// Read value and tell that we want to read the same address again.
		WaitForSPI1RXReady();
		index++;
	}
	values[index] = ACCESS(SPI1_DR) = (0);			// Read the final byte. Send 0 to stop reading.
	WaitForSPI1TXReady();
	ACCESS(GPIOE_BSRR) |= (1 << 2);			// Release slave again
} // End PCD_ReadRegister()
void PCD_SetRegisterBitMask(enum PCD_Register reg,	///< The register to update. One of the PCD_Register enums.
							byte mask			///< The bits to set.
									) { 
	byte tmp;
	tmp = PCD_ReadRegister(reg);
	PCD_WriteRegister(reg, tmp | mask);			// set bit mask
} // End PCD_SetRegisterBitMask()
/**
 * Writes a byte to the specified register in the MFRC522 chip.
 * The interface is described in the datasheet section 8.1.2.
 */
void AntennaOn(void) {
	char value = PCD_ReadRegister(TxControlReg);
	if ((value & 0x03) != 0x03) {
		PCD_WriteRegister(TxControlReg, value | 0x03);
	}
} // End AntennaOn()
void RFID_Init(void) {

	// Set the chipSelectPin as digital output, do not select the slave yet
	ACCESS(GPIOE_BSRR) |= (1 << 2);
		// First set the resetPowerDownPin as digital input, to check the MFRC522 power down mode.
    ACCESS(GPIOE_BSRR) |= (1 << 17);		// Make sure we have a clean LOW state.
    ACCESS(GPIOE_BSRR) |= (1 << 1);		// Make sure we have a clean HIGH state.
	
	// Reset baud rates
	PCD_WriteRegister(TxModeReg, 0x00);
	PCD_WriteRegister(RxModeReg, 0x00);
	// Reset ModWidthReg
	PCD_WriteRegister(ModWidthReg, 0x26);

	// When communicating with a PICC we need a timeout if something goes wrong.
	// f_timer = 13.56 MHz / (2*TPreScaler+1) where TPreScaler = [TPrescaler_Hi:TPrescaler_Lo].
	// TPrescaler_Hi are the four low bits in TModeReg. TPrescaler_Lo is TPrescalerReg.
	PCD_WriteRegister(TModeReg, 0x80);			// TAuto=1; timer starts automatically at the end of the transmission in all communication modes at all speeds
	PCD_WriteRegister(TPrescalerReg, 0xA9);		// TPreScaler = TModeReg[3..0]:TPrescalerReg, ie 0x0A9 = 169 => f_timer=40kHz, ie a timer period of 25μs.
	PCD_WriteRegister(TReloadRegH, 0x03);		// Reload timer with 0x3E8 = 1000, ie 25ms before timeout.
	PCD_WriteRegister(TReloadRegL, 0xE8);
	
	PCD_WriteRegister(TxASKReg, 0x40);		// Default 0x00. Force a 100 % ASK modulation independent of the ModGsPReg register setting
	PCD_WriteRegister(ModeReg, 0x3D);		// Default 0x3F. Set the preset value for the CRC coprocessor for the CalcCRC command to 0x6363 (ISO 14443-3 part 6.2.4)
	AntennaOn();						// Enable the antenna driver pins TX1 and TX2 (they were disabled by the reset)
} // End PCD_Init()
/**
 * Use the CRC coprocessor in the MFRC522 to calculate a CRC_A.
 * 
 * @return STATUS_OK on success, STATUS_??? otherwise.
 */
enum StatusCode PCD_CalculateCRC(	byte *data,		///< In: Pointer to the data to transfer to the FIFO for CRC calculation.
												byte length,	///< In: The number of bytes to transfer.
												byte *result	///< Out: Pointer to result buffer. Result is written to result[0..1], low byte first.
					 ) {
	PCD_WriteRegister(CommandReg, PCD_Idle);		// Stop any active command.
	PCD_WriteRegister(DivIrqReg, 0x04);				// Clear the CRCIRq interrupt request bit
	PCD_WriteRegister(FIFOLevelReg, 0x80);			// FlushBuffer = 1, FIFO initialization
	PCD_WriteRegister_3(FIFODataReg, length, data);	// Write data to the FIFO
	PCD_WriteRegister(CommandReg, PCD_CalcCRC);		// Start the calculation
	
	// Wait for the CRC calculation to complete. Each iteration of the while-loop takes 17.73μs.
	// TODO check/modify for other architectures than Arduino Uno 16bit

	// Wait for the CRC calculation to complete. Each iteration of the while-loop takes 17.73us.
	for (uint16_t i = 5000; i > 0; i--) {
		// DivIrqReg[7..0] bits are: Set2 reserved reserved MfinActIRq reserved CRCIRq reserved reserved
		byte n = PCD_ReadRegister(DivIrqReg);
		if (n & 0x04) {									// CRCIRq bit set - calculation done
			PCD_WriteRegister(CommandReg, PCD_Idle);	// Stop calculating CRC for new content in the FIFO.
			// Transfer the result from the registers to the result buffer
			result[0] = PCD_ReadRegister(CRCResultRegL);
			result[1] = PCD_ReadRegister(CRCResultRegH);
			return STATUS_OK;
		}
	}
	// 89ms passed and nothing happend. Communication with the MFRC522 might be down.
	return STATUS_TIMEOUT;
} // End PCD_CalculateCRC()
/**
 * Transfers data to the MFRC522 FIFO, executes a command, waits for completion and transfers data back from the FIFO.
 * CRC validation can only be done if backData and backLen are specified.
 *
 * @return STATUS_OK on success, STATUS_??? otherwise.
 */
enum StatusCode PCD_CommunicateWithPICC(	byte command,		///< The command to execute. One of the PCD_Command enums.
											byte waitIRq,		///< The bits in the ComIrqReg register that signals successful completion of the command.
											byte *sendData,		///< Pointer to the data to transfer to the FIFO.
											byte sendLen,		///< Number of bytes to transfer to the FIFO.
											byte *backData,		///< nullptr or pointer to buffer if data should be read back after executing the command.
											byte *backLen,		///< In: Max number of bytes to write to *backData. Out: The number of bytes returned.
											byte *validBits,	///< In/Out: The number of valid bits in the last byte. 0 for 8 valid bits.
											byte rxAlign,		///< In: Defines the bit position in backData[0] for the first bit received. Default 0.
											bool checkCRC		///< In: True => The last two bytes of the response is assumed to be a CRC_A that must be validated.
									 ) {
	// Prepare values for BitFramingReg
	byte txLastBits = validBits ? *validBits : 0;
	byte bitFraming = (rxAlign << 4) + txLastBits;		// RxAlign = BitFramingReg[6..4]. TxLastBits = BitFramingReg[2..0]
	
	PCD_WriteRegister(CommandReg, PCD_Idle);			// Stop any active command.
	PCD_WriteRegister(ComIrqReg, 0x7F);					// Clear all seven interrupt request bits
	PCD_WriteRegister(FIFOLevelReg, 0x80);				// FlushBuffer = 1, FIFO initialization
	PCD_WriteRegister_3(FIFODataReg, sendLen, sendData);	// Write sendData to the FIFO
	PCD_WriteRegister(BitFramingReg, bitFraming);		// Bit adjustments
	PCD_WriteRegister(CommandReg, command);				// Execute the command
	if (command == PCD_Transceive) {
		PCD_SetRegisterBitMask(BitFramingReg, 0x80);	// StartSend=1, transmission of data starts
	}
	
	// Wait for the command to complete.
	// In PCD_Init() we set the TAuto flag in TModeReg. This means the timer automatically starts when the PCD stops transmitting.
	// Each iteration of the do-while-loop takes 17.86μs.
	// TODO check/modify for other architectures than Arduino Uno 16bit
	uint16_t i;
	for (i = 2000; i > 0; i--) {
		byte n = PCD_ReadRegister(ComIrqReg);	// ComIrqReg[7..0] bits are: Set1 TxIRq RxIRq IdleIRq HiAlertIRq LoAlertIRq ErrIRq TimerIRq
		if (n & waitIRq) {					// One of the interrupts that signal success has been set.
			break;
		}
		if (n & 0x01) {						// Timer interrupt - nothing received in 25ms
			return STATUS_TIMEOUT;
		}
	}
	// 35.7ms and nothing happend. Communication with the MFRC522 might be down.
	if (i == 0) {
		return STATUS_TIMEOUT;
	}
	
	// Stop now if any errors except collisions were detected.
	byte errorRegValue = PCD_ReadRegister(ErrorReg); // ErrorReg[7..0] bits are: WrErr TempErr reserved BufferOvfl CollErr CRCErr ParityErr ProtocolErr
	if (errorRegValue & 0x13) {	 // BufferOvfl ParityErr ProtocolErr
		return STATUS_ERROR;
	}
  
	byte _validBits = 0;
	
	// If the caller wants data back, get it from the MFRC522.
	if (backData && backLen) {
		byte n = PCD_ReadRegister(FIFOLevelReg);	// Number of bytes in the FIFO
		if (n > *backLen) {
			return STATUS_NO_ROOM;
		}
		*backLen = n;											// Number of bytes returned
		PCD_ReadRegister_3(FIFODataReg, n, backData, rxAlign);	// Get received data from FIFO
		_validBits = PCD_ReadRegister(ControlReg) & 0x07;		// RxLastBits[2:0] indicates the number of valid bits in the last received byte. If this value is 000b, the whole byte is valid.
		if (validBits) {
			*validBits = _validBits;
		}
	}
	
	// Tell about collisions
	if (errorRegValue & 0x08) {		// CollErr
		return STATUS_COLLISION;
	}
	
	// Perform CRC_A validation if requested.
	if (backData && backLen && checkCRC) {
		// In this case a MIFARE Classic NAK is not OK.
		if (*backLen == 1 && _validBits == 4) {
			return STATUS_MIFARE_NACK;
		}
		// We need at least the CRC_A value and all 8 bits of the last byte must be received.
		if (*backLen < 2 || _validBits != 0) {
			return STATUS_CRC_WRONG;
		}
		// Verify CRC_A - do our own calculation and store the control in controlBuffer.
		byte controlBuffer[2];
		enum StatusCode status = PCD_CalculateCRC(&backData[0], *backLen - 2, &controlBuffer[0]);
		if (status != STATUS_OK) {
			return status;
		}
		if ((backData[*backLen - 2] != controlBuffer[0]) || (backData[*backLen - 1] != controlBuffer[1])) {
			return STATUS_CRC_WRONG;
		}
	}
	
	return STATUS_OK;
} // End PCD_CommunicateWithPICC()
/**
 * Executes the Transceive command.
 * CRC validation can only be done if backData and backLen are specified.
 * 
 * @return STATUS_OK on success, STATUS_??? otherwise.
 */
enum StatusCode PCD_TransceiveData(	byte *sendData,		///< Pointer to the data to transfer to the FIFO.
									byte sendLen,		///< Number of bytes to transfer to the FIFO.
									byte *backData,		///< nullptr or pointer to buffer if data should be read back after executing the command.
									byte *backLen,		///< In: Max number of bytes to write to *backData. Out: The number of bytes returned.
									byte *validBits,	///< In/Out: The number of valid bits in the last byte. 0 for 8 valid bits. Default nullptr.
									byte rxAlign,		///< In: Defines the bit position in backData[0] for the first bit received. Default 0.
									bool checkCRC		///< In: True => The last two bytes of the response is assumed to be a CRC_A that must be validated.
								 ) {
	byte waitIRq = 0x30;		// RxIRq and IdleIRq
	return PCD_CommunicateWithPICC(PCD_Transceive, waitIRq, sendData, sendLen, backData, backLen, validBits, rxAlign, checkCRC);
} // End PCD_TransceiveData()
/**
 * Transmits REQA or WUPA commands.
 * Beware: When two PICCs are in the field at the same time I often get STATUS_TIMEOUT - probably due do bad antenna design.
 * 
 * @return STATUS_OK on success, STATUS_??? otherwise.
 */ 
void PCD_ClearRegisterBitMask(enum	PCD_Register reg,	///< The register to update. One of the PCD_Register enums.
								byte mask			///< The bits to clear.
								) {
	byte tmp;
	tmp = PCD_ReadRegister(reg);
	PCD_WriteRegister(reg, tmp & (~mask));		// clear bit mask
} // End PCD_ClearRegisterBitMask()
enum StatusCode PICC_REQA_or_WUPA(	byte command, 		///< The command to send - PICC_CMD_REQA or PICC_CMD_WUPA
									byte *bufferATQA,	///< The buffer to store the ATQA (Answer to request) in
									byte *bufferSize	///< Buffer size, at least two bytes. Also number of bytes returned if STATUS_OK.
									) {
	byte validBits;
	enum StatusCode status;
	
	if (bufferATQA == NULL || *bufferSize < 2) {	// The ATQA response is 2 bytes long.
		return STATUS_NO_ROOM;
	}
	PCD_ClearRegisterBitMask(CollReg, 0x80);		// ValuesAfterColl=1 => Bits received after collision are cleared.
	validBits = 7;									// For REQA and WUPA we need the short frame format - transmit only 7 bits of the last (and only) byte. TxLastBits = BitFramingReg[2..0]
	status = PCD_TransceiveData(&command, 1, bufferATQA, bufferSize, &validBits,0,false);
	if (status != STATUS_OK) {
		return status;
	}
	if (*bufferSize != 2 || validBits != 0) {		// ATQA must be exactly 16 bits.
		return STATUS_ERROR;
	}
	return STATUS_OK;
} // End PICC_REQA_or_WUPA()
/**
 * Transmits a REQuest command, Type A. Invites PICCs in state IDLE to go to READY and prepare for anticollision or selection. 7 bit frame.
 * Beware: When two PICCs are in the field at the same time I often get STATUS_TIMEOUT - probably due do bad antenna design.
 * 
 * @return STATUS_OK on success, STATUS_??? otherwise.
 */
enum StatusCode PICC_RequestA(	byte *bufferATQA,	///< The buffer to store the ATQA (Answer to request) in
								byte *bufferSize	///< Buffer size, at least two bytes. Also number of bytes returned if STATUS_OK.
								) {
	return PICC_REQA_or_WUPA(PICC_CMD_REQA, bufferATQA, bufferSize);
} // End PICC_RequestA()
/**
 * Returns true if a PICC responds to PICC_CMD_REQA.
 * Only "new" cards in state IDLE are invited. Sleeping cards in state HALT are ignored.
 * 
 * @return bool
 */
bool PICC_IsNewCardPresent(void) {
	byte bufferATQA[2];
	byte bufferSize = sizeof(bufferATQA);

	// Reset baud rates
	PCD_WriteRegister(TxModeReg, 0x00);
	PCD_WriteRegister(RxModeReg, 0x00);
	// Reset ModWidthReg
	PCD_WriteRegister(ModWidthReg, 0x26);

	enum StatusCode result = PICC_RequestA(bufferATQA, &bufferSize);

	if (result == STATUS_OK || result == STATUS_COLLISION) {
		tag.atqa = ((uint16_t)bufferATQA[1] << 8) | bufferATQA[0];
		tag.ats.size = 0;
		tag.ats.fsc = 32;	// default FSC value

		// Defaults for TA1
		tag.ats.ta1.transmitted = false;
		tag.ats.ta1.sameD = false;
		tag.ats.ta1.ds = BITRATE_106KBITS;
		tag.ats.ta1.dr = BITRATE_106KBITS;

		// Defaults for TB1
		tag.ats.tb1.transmitted = false;
		tag.ats.tb1.fwi = 0;	// TODO: Don't know the default for this!
		tag.ats.tb1.sfgi = 0;	// The default value of SFGI is 0 (meaning that the card does not need any particular SFGT)

		// Defaults for TC1
		tag.ats.tc1.transmitted = false;
		tag.ats.tc1.supportsCID = true;
		tag.ats.tc1.supportsNAD = false;

		memset(tag.ats.data, 0, FIFO_SIZE - 2);

		tag.blockNumber = false;
		return true;
	}
	return false;
} // End PICC_IsNewCardPresent()
