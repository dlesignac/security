
package fr.eisti;

import java.io.UnsupportedEncodingException;



public class StringEncrypter
{
	static public String encrypt(String msg, String hdn) throws UnsupportedEncodingException
	{
		byte[] hdn_bytes = hdn.getBytes("UTF-8");
		
		for (byte b : hdn_bytes)
		{
			for (int i = 0; i < 8; i++)
			{
				if ((byte) ((b >> i) & 0x1) > 0)
				{
					msg += "\u200c";
				}
				else
				{
					msg += "\u200d";
				}
			}
		}
		
		return msg;
	}
	
	static public String decode(String msg) throws UnsupportedEncodingException
	{
		String hdn = "";
		
		byte[] msg_bytes = msg.getBytes("UTF-16");

		int  n = 0;
		byte current = 0;
		byte last = 0;
		
		for (byte b : msg_bytes)
		{
			if (last == 32)
			{
				if (b == 13) { n++; }
				if (b == 12) { current |= 1 << n; n++; }
				if (n == 8 ) { hdn += (char) current; current = 0; n = 0; }
			}
			
			last = b;
		}
		
		return hdn;
	}
}
