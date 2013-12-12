package ru.nsu.fit.g1201.races.view;

import ru.nsu.fit.g1201.races.ResultController;

import javax.swing.*;
import javax.swing.table.AbstractTableModel;
import java.awt.*;

public class TopScoresView extends JDialog {

    private ResultController resultController;

    public TopScoresView(ResultController resultController) {
        this.resultController = resultController;

        setResizable(false);

        JTable topScores = new JTable(new ScoresTableModel());
        topScores.setPreferredScrollableViewportSize(new Dimension(300, 160));
        topScores.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        JScrollPane scrollPane = new JScrollPane(topScores);
        scrollPane.setMaximumSize(new Dimension(300, 160));
        add(scrollPane);

        pack();
        setModalityType(Dialog.ModalityType.APPLICATION_MODAL);
        setTitle("Top scores");
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);
    }


    private final class ScoresTableModel extends AbstractTableModel {
        @Override
        public final int getRowCount() {
            return resultController.getTopScoresSize();
        }

        @Override
        public final int getColumnCount() {
            return 3;
        }

        @Override
        public final Object getValueAt(int r, int c) {
            switch (c) {
                case 0:
                    return resultController.getTopScores().get(r).getNickname();
                case 1:
                    return resultController.getTopScores().get(r).getScores();
                case 2:
                    return resultController.getTopScores().get(r).getMap();
                default:
                    return "";
            }
        }

        @Override
        public final String getColumnName(int c) {
            switch (c) {
                case 0:
                    return "Nickname";
                case 1:
                    return "Result";
                case 2:
                    return "Map";
                default:
                    return "";
            }
        }
    }
}
