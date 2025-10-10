using System;
using System.Threading;
using System.Net;
using System.Runtime.InteropServices;




namespace ContinuousGrab_cs
{
    class CallbackHandler : smcs.ICallbackEvent
    {
        #region ICallbackEvent Members
        // Warning! Callback handler is called in context of API thread and for real GUI app need to be synchronised to GUI thread.         
        public void OnConnect(smcs.IDevice device)
        {
            System.Console.WriteLine("Connected!");
        }

        public void OnDisconnect(smcs.IDevice device)
        {
            System.Console.WriteLine("Disconnected!");
        }

        public void OnLog(smcs.IDevice device, smcs.EventMessage message)
        {
            System.Console.WriteLine("Log: " + message.messageString);
        }

        #endregion
    }

    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            CallbackHandler eventHandler = new CallbackHandler();

            // initialize Camera API
            smcs.CameraSuite.InitCameraAPI();
            smcs.ICameraAPI smcsApi = smcs.CameraSuite.GetCameraAPI();

            if (!smcsApi.IsUsingKernelDriver())
            {
                Console.Out.WriteLine("Warning: Smartek Filter Driver not loaded.");
            }

            smcsApi.SetHeartbeatTime(3);
            smcsApi.RegisterCallback(eventHandler);

            // discover all devices on network
            smcsApi.FindAllDevices(3.0);
            smcs.IDevice[] devices = smcsApi.GetAllDevices();
            if (devices.Length <= 0) return;

            smcs.IDevice device = devices[0];
            if (device == null || !device.Connect())
            {
                Console.Out.WriteLine("Cannot connect to device: " +device.GetIpAddress().ToString() + " press any key to exit.");
                return;
            }

            string text;
            Int64 int64Value;

            Console.Out.WriteLine("Connected to first camera: " + device.GetIpAddress().ToString());
            if (device.GetStringNodeValue("DeviceVendorName", out text))
            {
                Console.Out.WriteLine("Device Vendor: " + text);
            }
            if (device.GetStringNodeValue("DeviceModelName", out text))
            {
                Console.Out.WriteLine("Device Model: " + text);
            }
            if (device.GetIntegerNodeValue("Width", out int64Value))
            {
                Console.Out.WriteLine("Width: " + int64Value);
            }
            if (device.GetIntegerNodeValue("Height", out int64Value))
            {
                Console.Out.WriteLine("Height: " + int64Value);
            }

            Int64 packetSize = 0;
            device.GetIntegerNodeValue("GevSCPSPacketSize", out packetSize);
            packetSize = packetSize & 0xFFFF;
            Console.Out.WriteLine("PacketSize: " + packetSize);

            // disable trigger mode
            bool status = device.SetStringNodeValue("TriggerMode", "Off");
            // set continuous acquisition mode
            status = device.SetStringNodeValue("AcquisitionMode", "Continuous");
            // start acquisition
            status = device.SetIntegerNodeValue("TLParamsLocked", 1);
            status = device.CommandNodeExecute("AcquisitionStart");

            Console.Out.WriteLine("Acquisition Start, press any key to exit loop...");

            bool isFirstImage = true;
            smcs.IImageInfo imageInfo = new smcs.IImageInfo();

            // acquire images
            while (!System.Console.KeyAvailable)
            {
                if (!device.GetImageInfo(ref imageInfo)) continue;

                if (isFirstImage)
                {
                    UInt32 sizeX, sizeY;
                    imageInfo.GetSize(out sizeX, out sizeY);
                    Console.Out.WriteLine("Acquiring image with size: " + sizeX + "x" + sizeY
                            + " ...");
                    UInt32 pendingImages = device.GetPendingImagesCount();
                    Console.Out.WriteLine("Pending images count: " + pendingImages);
                    isFirstImage = false;
                }
                else
                {
                    Console.Out.Write(".");
                }

                device.PopImage(imageInfo);
            }
            // stop acquisition
            status = device.CommandNodeExecute("AcquisitionStop");
            status = device.SetIntegerNodeValue("TLParamsLocked", 0);

            // disconnect from camera
            device.Disconnect();

            smcsApi.UnregisterCallback(eventHandler);
            smcs.CameraSuite.ExitCameraAPI();
            while (!System.Console.KeyAvailable) ;
        }
    }
}


