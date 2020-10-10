package tp7;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;
import javafx.scene.Parent;
import javafx.scene.Scene;

public class Source extends Application {

    @Override
    public void start(Stage primaryStage) {
        try {
    		Parent root = FXMLLoader.load(getClass().getClassLoader().getResource("View.fxml"));
            Scene scene = new Scene(root, 600, 400);
            scene.getRoot().requestFocus();
            primaryStage.setScene(scene);
            primaryStage.show();
    	} catch(Exception e) {
    		System.out.println(e.getMessage());
    	}
    }

    public static void main(String[] args) {
        launch(args);
    }

}