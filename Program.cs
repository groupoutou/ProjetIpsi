using System;
using smcs; // Assurez-vous d'importer le namespace smcs

class Program
{
    static void Main(string[] args)
    {
        // Initialiser CameraSuite
        smcs.CameraSuite.InitCameraAPI();
        smcs.ICameraAPI smcsApi = smcs.CameraSuite.GetCameraAPI();

        // Définir le temps de battement de coeur (optionnel)
        smcsApi.SetHeartbeatTime(3);

        // Enumérer les appareils
        smcsApi.FindAllDevices(2.0);
        smcs.IDevice[] devices = smcsApi.GetAllDevices();

        if (devices.Length == 0)
        {
            Console.WriteLine("Aucun appareil trouvé.");
            return;
        }

        // Sélectionner le premier appareil
        smcs.IDevice device = devices[0];
        Console.WriteLine("Appareil sélectionné : " + device.GetModelName());

        // Connexion à l'appareil
        bool status = device.Connect();
        if (!status)
        {
            Console.WriteLine("Échec de la connexion à l'appareil.");
            return;
        }

        // Utiliser l'appareil (exemple : capturer des images)
        CaptureImages(device);

        // Déconnexion et libération des ressources
        device.Disconnect();
        smcs.CameraSuite.ExitCameraAPI();
    }

    static void CaptureImages(smcs.IDevice device)
    {
        bool isFirstImage = true;
        smcs.IImageInfo imageInfo = null;

        while (true)
        {
            if (device.WaitForImage(3.0))
            {
                device.GetImageInfo(ref imageInfo);
                if (imageInfo != null)
                {
                    uint sizeX, sizeY;
                    imageInfo.GetSize(out sizeX, out sizeY);
                    Console.WriteLine("Image acquise avec taille : " + sizeX + "x" + sizeY);

                    // Traiter l'image ici

                    device.PopImage(imageInfo);
                }
            }
            else
            {
                Console.WriteLine("Aucune nouvelle image reçue.");
            }
        }
    }
}

