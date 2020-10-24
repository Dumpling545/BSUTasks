package lab3;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.Math;
import java.net.URLClassLoader;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import javax.management.StringValueExp;

public class MethodParser {
    private final String STRING_CHARACTER_PATTERN;
    private final String CHARACTER_PATTERN;
    private final String STRING_PATTERN;
    private final String BOOLEAN_PATTERN;
    private final String DECIMAL_INTEGER_PATTERN;
    private final String HEX_INTEGER_PATTERN;
    private final String OCTAL_INTEGER_PATTERN;
    private final String BINARY_INTEGER_PATTERN;
    private final String DECIMAL_FLOAT_PATTERN;
    private final String HEX_FLOAT_PATTERN;
    private final String METHOD_NAME_PATTERN;
    private final String METHOD_PARAMETER_PATTERN;
    private final String METHOD_PATTERN;

    private ClassLoader classLoader;

    public MethodParser(ClassLoader classLoader) {
        this.classLoader = classLoader;
        StringBuilder sb = new StringBuilder();
        STRING_CHARACTER_PATTERN = sb.append(
                "((\\\\u{1,}(([0-9a-fA-F][1-9a-fA-F][0-9a-fA-F]{2})|([1-9a-fA-F][0-9a-fA-F]{3})")
                .append("|(00[0-9a-fA-F&&[^025]][0-9a-fA-F])|(000[0-9a-fA-F&&[^acAC]])|")
                .append("(002[0-9a-fA-F&&[^2]])|(005[0-9a-fA-F&&[^cC]])))|")
                .append("([^\\n\\r\"\\\\])|(\\\\(b|t|n|f|r|\"|\'|(\\\\)|")
                .append("([0-7]{1,2})|([0-3][0-7]{2}))))").toString();
        sb.setLength(0);
        CHARACTER_PATTERN = sb.append(
                "'((\\\\u{1,}(([0-9a-fA-F][1-9a-fA-F][0-9a-fA-F]{2})|([1-9a-fA-F][0-9a-fA-F]{3})")
                .append("|(00[0-9a-fA-F&&[^025]][0-9a-fA-F])|(000[0-9a-fA-F&&[^acAC]])|")
                .append("(002[0-9a-fA-F&&[^7]])|(005[0-9a-fA-F&&[^cC]])))|")
                .append("([^\\n\\r\'\\\\])|(\\\\(b|t|n|f|r|\"|\'|(\\\\)|")
                .append("([0-7]{1,2})|([0-3][0-7]{2}))))'").toString();
        sb.setLength(0);
        STRING_PATTERN = sb.append("\"").append(STRING_CHARACTER_PATTERN).append("*\"").toString();
        BOOLEAN_PATTERN = "(true|false)";
        DECIMAL_INTEGER_PATTERN = "([+-]?(0|([1-9](_*[0-9]+)*))[lL]?)";
        HEX_INTEGER_PATTERN = "([+-]?0[xX]([0-9a-fA-F](_*[0-9a-fA-F]+)*)[lL]?)";
        OCTAL_INTEGER_PATTERN = "([+-]?0((_*[0-7]+)*)[lL]?)";
        BINARY_INTEGER_PATTERN = "([+-]?0[bB]([01](_*[01]+)*)[lL]?)";
        sb.setLength(0);
        DECIMAL_FLOAT_PATTERN = sb.append("([+-]?(([0-9](_*[0-9]+)*\\.([0-9](_*[0-9]+)*)?")
                .append("([eE][+-]?[0-9](_*[0-9]+)*)?[fFdD]?)|")
                .append("(\\.[0-9](_*[0-9]+)*([eE][+-]?[0-9](_*[0-9]+)*)?[fFdD]?)|")
                .append("([0-9](_*[0-9]+)*([eE][+-]?[0-9](_*[0-9]+)*)[fFdD]?)|")
                .append("([0-9](_*[0-9]+)*([eE][+-]?[0-9](_*[0-9]+)*)?[fFdD])))").toString();
        sb.setLength(0);
        HEX_FLOAT_PATTERN = sb.append("([+-]?((0[xX]([0-9a-fA-F](_*[0-9a-fA-F]+)*)(\\.)?")
                .append("([pP][+-]?[0-9](_*[0-9]+)*)[fFdD]?)|")
                .append("(0[xX]([0-9a-fA-F](_*[0-9a-fA-F]+)*)?\\.[0-9a-fA-F](_*[0-9a-fA-F]+)*))")
                .append("([pP][+-]?[0-9](_*[0-9]+)*)[fFdD]?)").toString();
        METHOD_NAME_PATTERN = "(([a-zA-Z_$][a-zA-Z\\d_$]*\\.)+([a-zA-Z_$][a-zA-Z\\d_$]*))";
        sb.setLength(0);
        METHOD_PARAMETER_PATTERN = sb.append(" (").append(String.class.getSimpleName()).append("|")
                .append(char.class.getName()).append("|").append(boolean.class.getName())
                .append("|").append(int.class.getName()).append("|").append(long.class.getName())
                .append("|").append(float.class.getName()).append("|")
                .append(double.class.getName()).append(") (").append(STRING_PATTERN).append("|")
                .append(CHARACTER_PATTERN).append("|").append(BOOLEAN_PATTERN).append("|")
                .append(HEX_FLOAT_PATTERN).append("|").append(DECIMAL_FLOAT_PATTERN).append("|")
                .append(BINARY_INTEGER_PATTERN).append("|").append(HEX_INTEGER_PATTERN).append("|")
                .append(OCTAL_INTEGER_PATTERN).append("|").append(DECIMAL_INTEGER_PATTERN)
                .append(")").toString();
        sb.setLength(0);
        METHOD_PATTERN = sb.append(METHOD_NAME_PATTERN).append("(").append(METHOD_PARAMETER_PATTERN)
                .append(")*").toString();
    }

    private Object parseAndRunMethod(String line) throws MethodParseException,
            ClassNotFoundException, NoSuchMethodException, SecurityException,
            IllegalAccessException, IllegalArgumentException, InvocationTargetException {
        Object result = null;
        if (line.matches(METHOD_PATTERN)) {
            Pattern namePattern = Pattern.compile(METHOD_NAME_PATTERN);
            Matcher nameMatcher = namePattern.matcher(line);
            nameMatcher.find();
            String fullMethodName = nameMatcher.group();
            int lastDotIndex = fullMethodName.lastIndexOf(".");
            String className = fullMethodName.substring(0, lastDotIndex);
            Class c = Class.forName(className, true, classLoader);
            String methodName = fullMethodName.substring(lastDotIndex + 1);
            int endName = nameMatcher.end();
            Pattern parameterPattern = Pattern.compile(METHOD_PARAMETER_PATTERN);
            Matcher parameterMatcher = parameterPattern.matcher(line);
            parameterMatcher.region(endName, line.length());
            List<Class> types = new ArrayList<>();
            List<Object> parameters = new ArrayList<>();
            while (parameterMatcher.find()) {
                types.add(primitiveForName(parameterMatcher.group(1)));
                parameters.add(parseLiteral(parameterMatcher.group(2), parameterMatcher.group(1)));
            }
             Method method = c.getMethod(methodName, types.toArray(new Class[types.size()]));
             result = method.invoke(null, parameters.toArray());
        } else {
            throw new MethodParseException(line);
        }
        return result;
    }
    private Class primitiveForName(String type){
        Class result = null;
        if (type.equals(int.class.getName())) {
            result = int.class;
        } else if (type.equals(long.class.getName())) {
            result = long.class;
        } else if (type.equals(float.class.getName())) {
            result = float.class;
        } else if (type.equals(double.class.getName())) {
            result = double.class;
        } else if (type.equals(boolean.class.getName())) {
            result = boolean.class;
        } else if (type.equals(char.class.getName())) {
            result = char.class;
        } else if (type.equals(String.class.getSimpleName())) {
            result = String.class;
        }
        return result;
    }
    private Object parseLiteral(String value, String type)
            throws MethodParseException, ArithmeticException {
        Object result = null;
        if (type.equals(int.class.getName())) {
            result = parseInt(value);
        } else if (type.equals(long.class.getName())) {
            result = parseLong(value);
        } else if (type.equals(float.class.getName())) {
            result = parseFloat(value);
        } else if (type.equals(double.class.getName())) {
            result = parseDouble(value);
        } else if (type.equals(boolean.class.getName())) {
            result = parseBoolean(value);
        } else if (type.equals(char.class.getName())) {
            result = parseChar(value);
        } else if (type.equals(String.class.getSimpleName())) {
            result = parseString(value);
        }
        return result;
    }

    private Object parseCharOrString(String value, String pattern) throws MethodParseException {
        if (!value.matches(pattern)) {
            throw new MethodParseException(value);
        }
        value = value.substring(1, value.length() - 1);
        StringBuilder sb = new StringBuilder(value.length());
        for (int i = 0; i < value.length(); i++) {
            char ch = value.charAt(i);
            if (ch == '\\') {
                char nextChar = (i == value.length() - 1) ? '\\' : value.charAt(i + 1);
                if (nextChar >= '0' && nextChar <= '7') {
                    StringBuilder octalCode = new StringBuilder(nextChar);
                    i++;
                    if ((i < value.length() - 1) && value.charAt(i + 1) >= '0'
                            && value.charAt(i + 1) <= '7') {
                        octalCode.append(value.charAt(++i));
                        if ((i < value.length() - 1) && value.charAt(i + 1) >= '0'
                                && value.charAt(i + 1) <= '7') {
                            octalCode.append(value.charAt(++i));
                        }
                    }
                    sb.append((char) Integer.parseInt(octalCode.toString(), 8));
                } else {
                    switch (nextChar) {
                        case '\\':
                            sb.append('\\');
                            i++;
                            break;
                        case 'b':
                            sb.append('\b');
                            i++;
                            break;
                        case 'f':
                            sb.append('\f');
                            i++;
                            break;
                        case 'n':
                            sb.append('\n');
                            i++;
                            break;
                        case 'r':
                            sb.append('\r');
                            i++;
                            break;
                        case 't':
                            sb.append('\t');
                            i++;
                            break;
                        case '\"':
                            sb.append('\"');
                            i++;
                            break;
                        case '\'':
                            sb.append('\'');
                            i++;
                            break;
                        case 'u':
                            i += 2;
                            while (value.charAt(i) == 'u')
                                i++;
                            int code = Integer.parseInt(value.substring(i, i + 4), 16);
                            i += 3;
                            sb.append(Character.toChars(code));
                            break;
                    }
                }
            } else {
                sb.append(ch);
            }
        }
        if (pattern.equals(CHARACTER_PATTERN)) {
            if (sb.length() > 1)
                throw new MethodParseException(value);
            return sb.charAt(0);
        } else {
            return sb.toString();
        }
    }

    private String parseString(String value) throws MethodParseException {
        return (String) parseCharOrString(value, STRING_PATTERN);
    }

    private boolean isChar(String value) {
        return value.matches(CHARACTER_PATTERN);
    }

    private char parseChar(String value) throws MethodParseException {
        return (char) parseCharOrString(value, CHARACTER_PATTERN);
    }

    private boolean parseBoolean(String value) throws MethodParseException {
        if (!value.matches(BOOLEAN_PATTERN)) {
            throw new MethodParseException(value);
        }
        return Boolean.parseBoolean(value);
    }

    private String normalizeNumberValue(String value) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < value.length(); i++) {
            switch (value.charAt(i)) {
                case '_':
                case 'l':
                case 'L':
                    break;
                default:
                    sb.append(value.charAt(i));
            }
        }
        return sb.toString();
    }

    private boolean isIntOrLong(String value) {
        return value.matches(DECIMAL_INTEGER_PATTERN) || value.matches(OCTAL_INTEGER_PATTERN)
                || value.matches(BINARY_INTEGER_PATTERN) || value.matches(HEX_INTEGER_PATTERN);
    }

    private boolean isInt(String value) {
        return isIntOrLong(value) && !value.endsWith("l") && !value.endsWith("L");
    }

    private int parseInt(String value) throws ArithmeticException, MethodParseException {
        int result = 0;
        if (!isInt(value) && !isChar(value)) {
            throw new MethodParseException(value);
        } else {
            result = Math.toIntExact(parseLong(value));
        }
        return result;
    }

    private long parseLong(String value) throws MethodParseException {
        long result = 0;
        if (!isIntOrLong(value) && !isChar(value)) {
            throw new MethodParseException(value);
        } else if (isChar(value)) {
            result = parseChar(value);
        } else {
            String normalized = normalizeNumberValue(value);
            if (!value.matches(BINARY_INTEGER_PATTERN)) {
                result = Long.decode(normalized);
            } else {
                result = Long.parseLong(normalized.substring(2), 2);
            }
        }
        return result;
    }


    private boolean isFloatOrDouble(String value) {
        return value.matches(DECIMAL_FLOAT_PATTERN) || value.matches(HEX_FLOAT_PATTERN);
    }

    private boolean isFloat(String value) {
        return isFloatOrDouble(value) && (value.endsWith("f") || value.endsWith("F"));
    }

    private float parseFloat(String value) throws MethodParseException {
        if (!isChar(value) && !isIntOrLong(value) && !isFloat(value)) {
            throw new MethodParseException(value);
        }
        return (float) parseDouble(value);
    }

    private double parseDouble(String value)
            throws MethodParseException, NumberFormatException, NullPointerException {
        double result = 0;
        if (!isChar(value) && !isIntOrLong(value) && !isFloatOrDouble(value)) {
            throw new MethodParseException(value);
        } else if (isChar(value)) {
            result = parseChar(value);
        } else if (isIntOrLong(value)) {
            result = parseLong(value);
        } else {
            result = Double.parseDouble(normalizeNumberValue(value));
        }
        return result;
    }

    public Map<String, Object> parseAndRunMethods(File file) throws IOException,
            MethodParseException, ClassNotFoundException, NoSuchMethodException, SecurityException,
            IllegalAccessException, IllegalArgumentException, InvocationTargetException {
        Map<String, Object> methodResults = new TreeMap<>();
        BufferedReader reader = new BufferedReader(new FileReader(file));
        String line = reader.readLine();
        while (line != null) {
            methodResults.put(line, parseAndRunMethod(line));
            line = reader.readLine();
        }
        reader.close();
        return methodResults;
    }
}
