package application;

import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyEvent;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class Controller {
	
	private TextLogger logger;

    @FXML
    private Label label;
    
    @FXML
    private TextArea logArea;
    
    public void initialize() {
    	Log log = new Log(logArea);
        MainCharacter character = new MainCharacter(label);
        
        logger = new TextLogger();
        logger.registerObserver(log);
        logger.registerObserver(character);
    }
        
    @FXML
    void keyPressed(KeyEvent event) {
        String s = event.getCode().getName();
        logger.setText(s);
        logArea.setScrollTop(Double.MAX_VALUE);
    }
}
