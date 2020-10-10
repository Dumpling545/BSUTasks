package tp7;
import javafx.scene.control.Label;

public class KeyboardButtonViewer implements Observer {
    private Label label;
    public KeyboardButtonViewer(Label label) {
        this.label = label;
    }
    
    @Override
    public void update(String s) {
    	label.setText(s);
    }
}