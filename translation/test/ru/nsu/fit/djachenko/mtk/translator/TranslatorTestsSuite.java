package ru.nsu.fit.djachenko.mtk.translator;

import org.junit.runner.RunWith;
import org.junit.runners.Suite;
import ru.nsu.fit.djachenko.mtk.translator.parser.expression.ExpressionParserTest;
import ru.nsu.fit.djachenko.mtk.translator.buffer.BufferTest;
import ru.nsu.fit.djachenko.mtk.translator.lexer.LexerTest;

@RunWith(Suite.class)
@Suite.SuiteClasses({
	BufferTest.class,
	LexerTest.class,
	ExpressionParserTest.class
})

public interface TranslatorTestsSuite
{
}
