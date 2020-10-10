package tp7;
public interface Observable {
    void registerObserver(Observer observer);
    void notifyObservers();
}
