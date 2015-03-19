package ru.nsu.fit.g1201.races;

import ru.nsu.fit.g1201.races.communication.MessageChannel;
import ru.nsu.fit.g1201.races.communication.MessageToView;
import ru.nsu.fit.g1201.races.communication.RequestForNicknameMessage;
import ru.nsu.fit.g1201.races.model.Result;
import ru.nsu.fit.g1201.races.model.TopScores;

import java.util.List;

public class ResultController {

	private TopScores topScores = new TopScores();
	private final MessageChannel<MessageToView> channel;

	private String nickname;

	public ResultController(MessageChannel<MessageToView> channel)
	{
		this.channel = channel;
	}

    public void newScores(long newScores, int mapIndex)
    {
        if (topScores.isTop(newScores))
        {
	        synchronized (this)
	        {
		        nickname = null;
		        channel.set(new RequestForNicknameMessage(this));

		        waitForSettingNickname();
	        }

            Result result = new Result();
            result.setNickname(nickname);
            result.setScore(newScores);
            result.setMapIndex(mapIndex); //TODO: взять мапу из race
            topScores.addResult(result);
        }
    }

    public List<Result> getTopScores() {
        return topScores.getTopScores();
    }

    public int getTopScoresSize() {
        return topScores.size();
    }

	public void waitForSettingNickname()
	{
		while (nickname == null)
		{
			try
			{
				wait();
			}
			catch (InterruptedException e)
			{
				e.printStackTrace();
			}
		}
	}

	public synchronized void setNickname(String nickname)
	{
		this.nickname = nickname;
		notify();
	}
}
