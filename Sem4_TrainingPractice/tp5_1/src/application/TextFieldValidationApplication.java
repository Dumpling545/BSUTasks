package application;

import java.awt.Insets;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.text.ParsePosition;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.util.Date;
import java.util.Locale;
import java.util.Scanner;

import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.text.Text;
import javafx.stage.Stage;
 
public class TextFieldValidationApplication extends Application implements EventHandler<Event> {
	private enum ValidationOption{
		NATURAL_NUMBER("Natural Number"),
		INTEGER_NUMBER("Integer Number"),
		FLOAT_NUMBER("Float Number"),
		DATE("Date"),
		TIME("Time"),
		EMAIL("Email");
		 private String option;
		 
		 ValidationOption(String option) {
	        this.option = option;
	    }
		 @Override
		public String toString() {
			return option;
		}
	}
	private BigDecimal parsedFloatValue;
	private ComboBox validationComboBox;
	private TextField validatedField;
	private Circle notificator;
    public static void main(String[] args) {
        launch(args);
    }
    
    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("Text field validation");
        validationComboBox = new ComboBox();
        for(ValidationOption option : ValidationOption.values())
        {
            validationComboBox.getItems().add(option);
        }
        validationComboBox.setValue(ValidationOption.NATURAL_NUMBER);
        validationComboBox.setOnAction(this);
        validatedField = new TextField();
        validatedField.setOnKeyTyped(this);
        notificator = new Circle();
        notificator.setRadius(10.0f);
        notificator.setFill(Color.RED);
        GridPane grid = new GridPane();
        grid.setVgap(5);
        grid.setHgap(5);
        grid.add(validationComboBox, 0, 0);
        grid.add(validatedField, 0, 1);
        grid.add(notificator, 1, 1);
        primaryStage.setScene(new Scene(grid, 300, 70));
        primaryStage.show();
    }
    void showValidationResult(boolean isValidated) {
    	if(isValidated) {
    		notificator.setFill(Color.LIGHTGREEN);
    	} else {
    		notificator.setFill(Color.RED);
    	}
    }
    boolean validateFloat(String text) {
    	return text.matches("\\A(\\+|\\-){0,1}(\\d+\\.?\\d?|\\d?\\.\\d+)(e(\\+|\\-){0,1}\\d+){0,1}\\z");
    }
    boolean validateInteger(String text) {
    	return text.matches("\\A[\\+\\-]{0,1}\\d+\\z");
    }
    boolean validateNatural(String text) {
    	return text.matches("\\A[1-9]\\d*\\z");
    }
    boolean validateDate(String text) {
    	return text.matches("\\A(((0[1-9]|1\\d|2[0-8])-(0[1-9]|1[0-2]))|((29|30)-(01|0[3-9]|1[0-2]))|(31-(01|03|05|07|08|10|12)))-\\d{4}\\z");
    }

    boolean validateTime(String text) {
    	return text.matches("\\A([0-1][0-9]|[2][0-3]):([0-5][0-9])\\z");
    }
    boolean validateEmail(String text) {
    	return text.matches("\\A\\w+(\\.\\w+|\\w?)+@[a-zA-Z0-9]+(_[a-zA-Z0-9]+|[a-zA-Z0-9]?)*(\\.[a-zA-Z]{2,3})+\\z");
    }
    
	@Override
	public void handle(Event arg0) {
		ValidationOption option = (ValidationOption)validationComboBox.getValue();
		String text = validatedField.getText().trim();
		boolean isValidated = false;
		switch(option) {
			case NATURAL_NUMBER:
				isValidated = validateNatural(text);
				break;
			case INTEGER_NUMBER:
				isValidated = validateInteger(text);
				break;
			case FLOAT_NUMBER:
				isValidated = validateFloat(text);
				break;
			case DATE:
				isValidated = validateDate(text);
				break;
			case TIME:
				isValidated = validateTime(text);
				break;
			case EMAIL:
				isValidated = validateEmail(text);
				break;
		}
		showValidationResult(isValidated);
	}
}
