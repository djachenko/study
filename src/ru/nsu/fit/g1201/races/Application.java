package ru.nsu.fit.g1201.races;


import ru.nsu.fit.g1201.races.view.MainWindow;

import javax.swing.*;

public final class Application {

    public static void main(String[] args) {

        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                RaceParameters sc = new RaceParameters();
                MainWindow mw = new MainWindow(sc);
                mw.setVisible(true);
            }
        });

    }

}

