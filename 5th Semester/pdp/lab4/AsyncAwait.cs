namespace HTTPDownloader;

public static class AsyncAwait
{
    public static void Run(List<string> urls)
    {
        var futures = urls.Select((t, i) => SocketHandler.Create(t, "/", i)).Select(socketHandler => Task.Run(() => Start(socketHandler))).ToList();
        Task.WhenAll(futures).Wait();
    }

    private static async Task Start(SocketHandler socketHandler)
    {
        await socketHandler.BeginConnectAsync();
        Console.WriteLine($"Async Await-{socketHandler.Id}: Socket connected to {socketHandler.BaseUrl} ({socketHandler.UrlPath})");
        
        var numberOfSentBytes = await socketHandler.BeginSendAsync();
        Console.WriteLine($"Async Await-{socketHandler.Id}: Sent {numberOfSentBytes} bytes to {socketHandler.BaseUrl} ({socketHandler.UrlPath})");
        
        await socketHandler.BeginReceiveAsync();
        var header = Parser.GetHeader(socketHandler.GetResponseContent);
        var contentLength = Parser.GetContentLength(header);
        Console.WriteLine($"Async Await-{socketHandler.Id}: Received response from {socketHandler.BaseUrl} ({socketHandler.UrlPath}) with \n {header} \nhaving Content Length = {contentLength}\n");

        socketHandler.ShutdownAndClose();
    }
}