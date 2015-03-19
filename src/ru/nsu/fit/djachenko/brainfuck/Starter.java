package ru.nsu.fit.djachenko.brainfuck;

public class Starter
{
	public static void main(String[] args)
	{
		new Interpreter(new Parser("" +
		                           "++++++++" +
		                           "[" +
		                           ">++++" +
		                           "[" +
		                           ">++" +
		                           ">+++" +
		                           ">+++" +
		                           ">+" +
		                           "<<<<-" +
		                           "]" +
		                           ">+" +
		                           ">+" +
		                           ">-" +
		                           ">>+" +
		                           "[<]" +
		                           "<-" +

		                           "]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++."), new DataManager()).run();
	}
}
