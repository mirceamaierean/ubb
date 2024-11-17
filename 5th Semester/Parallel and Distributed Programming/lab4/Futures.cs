namespace HTTPDownloader;

public static class Futures
{
    public static void Run(IEnumerable<string> urls)
    {
        var futures = urls.Select((t, i) => SocketHandler.Create(t, "/", i)).Select(socketHandler => Task.Run(() => Start(socketHandler))).ToList();
        Task.WhenAll(futures).Wait();
    }

    private static Task Start(SocketHandler socketHandler)
    {
        socketHandler.BeginConnectAsync().Wait();
        Console.WriteLine($"Callback-{socketHandler.Id}: Socket connected to {socketHandler.BaseUrl} ({socketHandler.UrlPath})");
        
        var sendTask = socketHandler.BeginSendAsync();
        sendTask.Wait();
        var numberOfSentBytes = sendTask.Result;
        Console.WriteLine($"Futures-{socketHandler.Id}: Sent {numberOfSentBytes} bytes to {socketHandler.BaseUrl} ({socketHandler.UrlPath})");
        
        socketHandler.BeginReceiveAsync().Wait();
        
        var header = Parser.GetHeader(socketHandler.GetResponseContent);
        var contentLength = Parser.GetContentLength(header);
        Console.WriteLine($"Futures-{socketHandler.Id}: Received response from {socketHandler.BaseUrl} ({socketHandler.UrlPath}) with \n {header} \nhaving Content Length = {contentLength}\n");
        socketHandler.ShutdownAndClose();
        return Task.CompletedTask;
    }
}