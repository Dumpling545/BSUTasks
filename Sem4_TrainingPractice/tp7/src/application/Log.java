package application;

import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.text.Text;

public class Log implements Observer {
    private TextArea area;

    public Log(TextArea area) {
        this.area = area;
    }

    @Override
    public void update(String s) {
    	area.setText(area.getText()+ "\n" + s + " pressed");
    }
}
