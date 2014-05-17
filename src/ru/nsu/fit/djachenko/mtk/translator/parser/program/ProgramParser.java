package ru.nsu.fit.djachenko.mtk.translator.parser.program;

import ru.nsu.fit.djachenko.mtk.translator.lexer.Lexeme;
import ru.nsu.fit.djachenko.mtk.translator.lexer.Lexer;
import ru.nsu.fit.djachenko.mtk.translator.lexer.LexerException;
import ru.nsu.fit.djachenko.mtk.translator.parser.Type;
import ru.nsu.fit.djachenko.mtk.translator.parser.expression.ExpressionParser;
import ru.nsu.fit.djachenko.mtk.translator.parser.expression.ExpressionParserException;
import ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree.Expression;
import ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree.Variable;
import ru.nsu.fit.djachenko.mtk.translator.parser.program.tree.*;

import java.io.IOException;
import java.util.*;

public class ProgramParser
{
	private static class VariableIndexGenerator
	{
		private int count = 0;

		int getIndex()
		{
			int temp = count;

			count += 2;

			return temp;
		}
	}

	private final Lexer lexer;

	private final ExpressionParser expressionParser;

	private final Map<String, Method> methodMap = new HashMap<>();
	private final Map<String, Variable> variableMap = new HashMap<>();

	{
		methodMap.put("print", new Print());
	}

	public ProgramParser(Lexer lexer)
	{
		this.lexer = lexer;

		expressionParser = new ExpressionParser(lexer, variableMap);
	}

	public Program parseProgram() throws IOException, LexerException, ExpressionParserException, ProgramParserException
	{
		List<Method> methods = new LinkedList<>();

		methods.add(methodMap.get("print"));

		while (lexer.getLexeme().getType() != Lexeme.Type.END_OF_PROGRAM)
		{
			lexer.reject();

			Method method = parseMethod();

			methodMap.put(method.getName(), method);
			methods.add(method);
		}

		return new Program(methods);
	}

	public Method parseMethod() throws IOException, LexerException, ExpressionParserException, ProgramParserException
	{
		VariableIndexGenerator generator = new VariableIndexGenerator();

		Type returnType = parseType();
		String name = lexer.getLexeme().getValue();//TODO: check

		if (lexer.getLexeme().getType() != Lexeme.Type.OPEN_PARENTHESIS)
		{
			lexer.reject();

			fail("Unexpected identifier ", lexer.getLexeme());
		}

		List<Parameter> parameters = parseVarlist(generator);

		if (lexer.getLexeme().getType() != Lexeme.Type.OPEN_BRACE)
		{
			lexer.reject();

			fail("Unexpected identifier ", lexer.getLexeme());
		}

		List<Statement> body = parseBody(generator);

		return new Method(returnType, name, parameters, body);
	}

	private List<Parameter> parseVarlist(VariableIndexGenerator generator) throws IOException, LexerException, ProgramParserException
	{
		List<Parameter> parameters = new ArrayList<>();

		Lexeme currentLexeme;

		for (currentLexeme = lexer.getLexeme(); currentLexeme.getType() == Lexeme.Type.TYPE; currentLexeme = lexer.getLexeme())
		{
			lexer.reject();

			parameters.add(parseDeclaration(generator));
		}

		if (currentLexeme.getType() != Lexeme.Type.CLOSE_PARENTHESIS)
		{
			fail("Unexpected identifier ", currentLexeme);
		}

		return parameters;
	}

	private List<Statement> parseBody(VariableIndexGenerator generator) throws IOException, LexerException, ExpressionParserException, ProgramParserException
	{
		List<Statement> statements = new LinkedList<>();

		Lexeme currentLexeme;

		for (currentLexeme = lexer.getLexeme(); currentLexeme.getType() != Lexeme.Type.CLOSE_BRACE; currentLexeme = lexer.getLexeme())
		{
			if (currentLexeme.getType() == Lexeme.Type.END_OF_PROGRAM)
			{
				fail("Unexpected identifier ", currentLexeme);
			}
			else
			{
				lexer.reject();

				statements.add(parseStatement(generator));
			}
		}

		return new ArrayList<>(statements);
	}

	private Statement parseStatement(VariableIndexGenerator generator) throws IOException, LexerException, ExpressionParserException, ProgramParserException
	{
		Lexeme currentLexeme = lexer.getLexeme();
		lexer.reject();

		switch (currentLexeme.getType())
		{
			case TYPE:
				return parseDeclaration(generator);
			case IDENTIFIER:
				if (variableMap.containsKey(currentLexeme.getValue()))
				{
					return parseAssignment();
				}
				else if (methodMap.containsKey(currentLexeme.getValue()))
				{
					return parseCall();
				}
				else
				{
					fail("Unexpected identifier ", currentLexeme);
				}

			default:
				break;
		}

		return null;
	}

	private Parameter parseDeclaration(VariableIndexGenerator generator) throws IOException, LexerException
	{
		Type type = parseType();

		String name = lexer.getLexeme().getValue();

		variableMap.put(name, new Variable(type, name, generator.getIndex()));

		return new Parameter(type);
	}

	private Assignment parseAssignment() throws IOException, LexerException, ExpressionParserException, ProgramParserException
	{
		String name = lexer.getLexeme().getValue();
		Lexeme sign = lexer.getLexeme();
		Expression value = parseValue();

		Variable variable = variableMap.get(name);

		if (!value.getType().isCastableTo(variable.getType()))
		{
			throw new ProgramParserException("Assignment type mismatch " + variable.getName());
		}

		return new Assignment(variable, value);
	}

	private Expression parseValue() throws IOException, LexerException, ExpressionParserException
	{
		Lexeme lexeme = lexer.getLexeme();
		lexer.reject();

		if (methodMap.containsKey(lexeme.getValue()))
		{
			return parseCall();
		}
		else
		{
			return expressionParser.parseExpression();
		}
	}

	private Type parseType() throws IOException, LexerException
	{
		Lexeme currentLexeme = lexer.getLexeme();

		return Type.getType(currentLexeme.getValue());
	}

	private Call parseCall() throws IOException, LexerException
	{
		String name = lexer.getLexeme().getValue();

		Lexeme lexeme = lexer.getLexeme();

		List<Variable> parameters = new LinkedList<>();

		for (Lexeme currentLexeme = lexer.getLexeme(); currentLexeme.getType() == Lexeme.Type.IDENTIFIER; currentLexeme = lexer.getLexeme())
		{
			String parameterName = currentLexeme.getValue();

			parameters.add(variableMap.get(parameterName));
		}

		return new Call(methodMap.get(name), parameters);
	}

	private static void fail(String message, Lexeme cause) throws ProgramParserException
	{
		throw new ProgramParserException(message +
		                                 cause.getValue() +
		                                 " at line " +
		                                 cause.getLine() +
		                                 ", column " +
		                                 cause.getColumn());
	}
}
