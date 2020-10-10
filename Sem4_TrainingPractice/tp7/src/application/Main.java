package application;
import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Pos;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.StackPane;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.scene.text.TextAlignment;
import javafx.stage.Stage;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.ScrollPane;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) {
    	

        try {
    		Parent root = FXMLLoader.load(getClass().getResource("View.fxml"));
            Scene scene = new Scene(root, 600, 400);
            
            scene.getRoot().requestFocus();
            primaryStage.setScene(scene);
            primaryStage.show();
    	} catch(Exception e) {
    		e.printStackTrace();
    	}


    }

    public static void main(String[] args) {
        launch(args);
    }

}