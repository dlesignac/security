
package fr.eisti;

import java.io.UnsupportedEncodingException;



public class Main
{
	public static void main(String[] args)
	{
		try
		{
			String msg = StringEncrypter.encrypt("Coucou", "salut");
			System.out.println(msg);
			String hdn = StringEncrypter.decode(msg);
			System.out.println(hdn);
		}
		catch (UnsupportedEncodingException e)
		{
			e.printStackTrace();
		}
	}
}
