package lab3;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.List;
import javax.tools.JavaCompiler;
import javax.tools.ToolProvider;

public class SimpleClassCompiler {
    public static URL compileAndGetParentUrl(File file)
            throws ClassNotFoundException, IOException, CannotCompileJavaFileException {
        JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();
        int result = compiler.run(null, null, null, file.getPath());
        if (result != 0) {
            throw new CannotCompileJavaFileException(file);
        }
        return file.getParentFile().toURI().toURL();
    }

    public static ClassLoader getClassLoaderWithPrecompiledJavaFiles(List<File> javaFiles)
            throws ClassNotFoundException, CannotCompileJavaFileException, IOException {
        URL[] urls = new URL[javaFiles.size()];
        for (int i = 0; i < javaFiles.size(); i++) {
            urls[i] = SimpleClassCompiler.compileAndGetParentUrl(javaFiles.get(i));
        }
        ClassLoader loader = URLClassLoader.newInstance(urls);
        return loader;
    }
}
