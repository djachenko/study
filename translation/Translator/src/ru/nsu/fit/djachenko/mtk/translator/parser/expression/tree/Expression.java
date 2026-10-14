package ru.nsu.fit.djachenko.mtk.translator.parser.expression.tree;

import ru.nsu.fit.djachenko.mtk.translator.parser.Type;

public interface Expression
{
	double count();
	String toCode();
	Type getType();
}
