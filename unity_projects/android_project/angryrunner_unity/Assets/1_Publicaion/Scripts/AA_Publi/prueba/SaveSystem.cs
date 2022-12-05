using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using UnityEngine;

public static class SaveSystem
{
  public static void SavePlayer(Player player)
  {

    string path = Application.persistentDataPath + "./juego66.game";
    BinaryFormatter formatter = new BinaryFormatter();
    FileStream stream = new FileStream(path, FileMode.OpenOrCreate);

    PlayerData data = new PlayerData(player);

    formatter.Serialize(stream, data);
    stream.Close();
  }

  public static PlayerData LoadPlayer()
  {
    string path = Application.persistentDataPath + "./juego66.game";
    if (File.Exists(path))
    {
      BinaryFormatter formatter = new BinaryFormatter();
      FileStream stream = new FileStream(path, FileMode.OpenOrCreate);

      PlayerData data = formatter.Deserialize(stream) as PlayerData;

      stream.Close();
      return data;
    }
    else
    {
      Debug.Log("Save file not found");
      return null;
    }
  }
}
