namespace HTTPDownloader;

public static class Parser
{
    public static string GetHeader(string response)
    {
        var index = response.IndexOf("\r\n\r\n", StringComparison.Ordinal);
        return response.Substring(0, index);
    }
    
    public static string GetContentLength(string header)
    {
        var index = header.IndexOf("Content-Length:", StringComparison.OrdinalIgnoreCase);
        var start = header.IndexOf(" ", index, StringComparison.OrdinalIgnoreCase) + 1;
        var end = header.IndexOf("\r\n", start, StringComparison.OrdinalIgnoreCase);
        return header.Substring(start, end - start);
    }
}