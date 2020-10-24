package lab3;

import java.io.File;

public class CannotCompileJavaFileException extends RuntimeException{
    public CannotCompileJavaFileException(File file){
        super("File" + file.getName() + " cannot be compiled!");
    }
}
