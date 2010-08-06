package br.unipe.m2asm.machine;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

/**
 * @author User
 *
 */
public class M2ExeHeader {
	//assinatura
	private byte signature[] = new byte[] { 'M', '2' };
	private byte versionMajor = Machine.VERSION_MAJOR, versionMinor = Machine.VERSION_MINOR;
	//tam. segmento de código
	public int codeSize;
	//tam. segmento de dados inicializados
	public int dataSize;
	//tam. segmento de dados não inicializados
	public int nonInitDataSize;
	//tam. segmento de pilha
	public int stackSize;
	//reservado para uso futuro
	private byte reserved[] = new byte[8];
	
	public M2ExeHeader() {
		
	}
	
	private int getSize() {
		return signature.length +
				2 +							// versionMajor, versionMinor
				Machine.WORD_SIZE +			// codeSize
				Machine.WORD_SIZE +			// dataSize
				Machine.WORD_SIZE +			// nonInitDataSize
				Machine.WORD_SIZE +			// stackDataSize
				reserved.length;
	}
	
	public byte[] getBytes() {
		ByteBuffer buff = ByteBuffer.allocate(getSize());
		buff.order(ByteOrder.LITTLE_ENDIAN);
		buff.put(signature);
		buff.put(versionMajor);
		buff.put(versionMinor);
		buff.putInt(codeSize);
		buff.putInt(dataSize);
		buff.putInt(nonInitDataSize);
		buff.putInt(stackSize);
		buff.put(reserved);
		return buff.array();
	}
}
