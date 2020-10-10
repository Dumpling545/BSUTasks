package application;
import javafx.scene.control.Label;
import javafx.scene.text.Text;

public class MainCharacter implements Observer {
    private Label label;

    public MainCharacter(Label label) {
        this.label = label;
    }

    @Override
    public void update(String s) {
    	label.setText(s);
    }
}