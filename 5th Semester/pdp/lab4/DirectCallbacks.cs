namespace HTTPDownloader;

public static class DirectCallbacks
{
    public static void Run(List<string> urls)
    {
        for (int i = 0; i < urls.Count; i++)
        {
            var socketHandler = SocketHandler.Create(urls[i], "/", i);
            Start(socketHandler);
        }
        Thread.Sleep(100000);
    }

    private static void Start(SocketHandler socketHandler)
    {
        socketHandler.StartConnect(HandleConnected);
    }

    private static void HandleConnected(SocketHandler socketHandler)
    {
        Console.WriteLine($"Callback-{socketHandler.Id}: Socket connected to {socketHandler.BaseUrl} ({socketHandler.UrlPath})");
        socketHandler.StartSend(HandleSent);
    }

    private static void HandleSent(SocketHandler socketHandler, int numberOfSentBytes)
    {
        Console.WriteLine($"Callback-{socketHandler.Id}: Sent {numberOfSentBytes} bytes to {socketHandler.BaseUrl} ({socketHandler.UrlPath})");
        socketHandler.StartReceive(HandleReceived);
    }

    private static void HandleReceived(SocketHandler socketHandler)
    {
        var header = Parser.GetHeader(socketHandler.GetResponseContent);
        var contentLength = Parser.GetContentLength(header);
        Console.WriteLine($"Callback-{socketHandler.Id}: Received response from {socketHandler.BaseUrl} ({socketHandler.UrlPath}) with \n {header} \nhaving Content Length = {contentLength}\n");
        socketHandler.ShutdownAndClose();
    }
}