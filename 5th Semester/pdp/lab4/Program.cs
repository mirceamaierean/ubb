using HTTPDownloader;

List<string> urls =
[
    "wonderfullushbrightspell.neverssl.com",
    "targetedattacks.trendmicro.com",
    "streamhd4k.com",
    "w3.com",
    "go.com",
    "socialstudieshelp.com"
];

Console.WriteLine("1. Callback Solution");
Console.WriteLine("2. Futures Solution");
Console.WriteLine("3. Async Await Solution");

var choice = Console.ReadLine();

switch (choice)
{
    case "1":
        DirectCallbacks.Run(urls);
        break;
    case "2":
        Futures.Run(urls);
        break;
    case "3":
        AsyncAwait.Run(urls);
        break;
    default:
        Console.WriteLine("Invalid choice");
        break;
}

