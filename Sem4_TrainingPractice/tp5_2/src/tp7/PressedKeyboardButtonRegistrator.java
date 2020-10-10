package tp7;

import java.util.ArrayList;
import java.util.List;

public class PressedKeyboardButtonRegistrator implements Observable {
    private List<Observer> observers = new ArrayList<>();
    private String newText;
    @Override
    public void registerObserver(Observer observer) {
        if (observer != null) {
            observers.add(observer);
        }
    }
    @Override
    public void notifyObservers() {
        for (Observer elem : observers) {
            elem.update(newText);
        }
    }
    public void setText(String s){
        newText = s;
        notifyObservers();
    }

}
