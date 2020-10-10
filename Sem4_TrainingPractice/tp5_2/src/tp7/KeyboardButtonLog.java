package tp7;

import javafx.scene.control.TextArea;

public class KeyboardButtonLog implements Observer {
    private TextArea textArea;
    public KeyboardButtonLog(TextArea textArea) {
        this.textArea = textArea;
    }
    
    @Override
    public void update(String s) {
    	StringBuilder sb = new StringBuilder(s);
    	sb.append(" pressed\n");
    	sb.append(textArea.getText());
    	textArea.setText(sb.toString());
    }
}
