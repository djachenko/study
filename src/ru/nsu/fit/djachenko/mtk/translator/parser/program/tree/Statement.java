package ru.nsu.fit.djachenko.mtk.translator.parser.program.tree;

import ru.nsu.fit.djachenko.mtk.translator.parser.Type;

public interface Statement
{
	public String toCode();
	public Type getType();
}
