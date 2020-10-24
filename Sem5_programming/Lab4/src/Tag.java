public class Tag {
    private int startLine;
    private int startColumn;
    private int endLine;
    private int endColumn;
    private String name;
    private String fullName;

    public Tag(String name, int startLine, int startColumn, String fullName) {
        this.startLine = startLine;
        this.startColumn = startColumn;
        this.name = name;
        this.fullName = fullName;
    }

    public Tag(int startLine, int startColumn, int endLine, int endColumn, String fullName) {
        this.startLine = startLine;
        this.startColumn = startColumn;
        this.endLine = endLine;
        this.endColumn = endColumn;
        this.fullName = fullName;
    }

    public void close(int endLine, int endColumn) {
        this.endLine = endLine;
        this.endColumn = endColumn;
    }

    public boolean isOpeningTagOf(String endName) {
        return name.equals(endName);
    }

    public int getStartLine() {
        return startLine;
    }


    public int getStartColumn() {
        return startColumn;
    }

    public int getEndLine() {
        return endLine;
    }

    public int getEndColumn() {
        return endColumn;
    }

    public String getFullName() {
        return fullName;
    }
}
