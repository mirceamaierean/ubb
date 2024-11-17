using System.Net;
using System.Net.Sockets;
using System.Text;

namespace HTTPDownloader;

public class SocketHandler : Socket
{
    public int Id { get; }

    public string BaseUrl { get; }

    public string UrlPath { get; }

    private IPEndPoint EndPoint { get; }

    private StringBuilder ResponseContent { get; } = new();

    private const int DefaultHttpPort = 80;
    private const int BufferSize = 1024;
    
    public static SocketHandler Create(string baseUrl, string urlPath, int id)
    {
        IPHostEntry? ipHostInformation = null;

        Console.WriteLine($"Resolving {baseUrl}");
        
        do
        {
            try
            {
                ipHostInformation = Dns.GetHostEntry(baseUrl);
            }
            catch (SocketException)
            {
                Console.WriteLine("DNS Failed, trying to connect again in 1 second");
                Thread.Sleep(1000);
            }
        } while (ipHostInformation == null);
        
        
        var ipAddress = ipHostInformation.AddressList[0];
        
        return new SocketHandler(baseUrl, urlPath, ipAddress, id);
    }

    private SocketHandler(string baseUrl, string urlPath, IPAddress ipAddress, int id) : base(ipAddress.AddressFamily,
        SocketType.Stream, ProtocolType.Tcp)
    {
        Id = id;
        BaseUrl = baseUrl;
        UrlPath = urlPath;
        EndPoint = new IPEndPoint(ipAddress, DefaultHttpPort);
    }

    public void StartConnect(Action<SocketHandler> onConnected)
    {
        BeginConnect(EndPoint, ar =>
        {
            EndConnect(ar);
            onConnected(this);
        }, null);
    }

    public void StartSend(Action<SocketHandler, int> onSent)
    {
        var requestString = $"GET {UrlPath} HTTP/1.1\r\nHost: {BaseUrl}\r\nContent-Length: 0\r\n\r\n";
        var requestBytes = Encoding.ASCII.GetBytes(requestString);

        BeginSend(requestBytes, 0, requestBytes.Length, SocketFlags.None, ar =>
        {
            var bytesSent = EndSend(ar);
            onSent(this, bytesSent);
        }, null);
    }
    
    public void StartReceive(Action<SocketHandler> onReceived)
    {
        var buffer = new byte[BufferSize];
        ResponseContent.Clear();

        BeginReceive(buffer, 0, BufferSize, SocketFlags.None, ar =>
        {
            HandleReceiveResult(ar, buffer, onReceived);
        }, null);
    }

    private void HandleReceiveResult(IAsyncResult ar, byte[] buffer, Action<SocketHandler> onReceived)
    {
        var numberOfReadBytes = EndReceive(ar);
        ResponseContent.Append(Encoding.ASCII.GetString(buffer, 0, numberOfReadBytes));

        if (!ResponseContent.ToString().Contains("</html>"))
        {
            BeginReceive(buffer, 0, BufferSize, SocketFlags.None, ar2 =>
            {
                HandleReceiveResult(ar2, buffer, onReceived);
            }, null);
            return;
        }
        onReceived(this);
    }

    public Task BeginConnectAsync() => Task.Run(() =>
    {
        var taskCompletion = new TaskCompletionSource();

        StartConnect(_ => { taskCompletion.TrySetResult(); });
        
        return taskCompletion.Task;
    });

    public Task<int> BeginSendAsync() => Task.Run(() =>
    {
        var taskCompletion = new TaskCompletionSource<int>();
        StartSend((_, numberOfSentBytes) => taskCompletion.TrySetResult(numberOfSentBytes));

        return taskCompletion.Task;
    });
    
    public Task BeginReceiveAsync() => Task.Run(() =>
    {
        var taskCompletion = new TaskCompletionSource();
        StartReceive(_ => taskCompletion.TrySetResult());

        return taskCompletion.Task;
    });
    
    
    public void ShutdownAndClose()
    {
        Shutdown(SocketShutdown.Both);
        Close();
    }
    
    public string GetResponseContent => ResponseContent.ToString();

}