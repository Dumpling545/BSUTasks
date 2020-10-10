package tp7;

import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.input.KeyEvent;


public class Controller {	
	private PressedKeyboardButtonRegistrator registrator;
	
    @FXML
    private Label viewerLabel;
    
    @FXML
    private TextArea logTextArea;
    
    public void initialize() {
    	KeyboardButtonLog keyboardButtonLog = new KeyboardButtonLog(logTextArea);
        KeyboardButtonViewer keyboardButtonViewer = new KeyboardButtonViewer(viewerLabel);
        registrator = new PressedKeyboardButtonRegistrator();
        registrator.registerObserver(keyboardButtonLog);
        registrator.registerObserver(keyboardButtonViewer);
    }
    
    @FXML
    void onKeyPressed(KeyEvent event) {
        String s = event.getCode().getName();
        registrator.setText(s);
    }
}
