using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using UnityEngine;

public static class SaveData
{
    public static void SavesData(copyLevels aa)
    {
      BinaryFormatter formatter = new BinaryFormatter();
      string path = Application.persistentDataPath + "/juego.game";
      FileStream stream = new FileStream(path, FileMode.Create);

      SaveLevels data = new SaveLevels(aa);

      formatter.Serialize(stream, aa);
      stream.Close();
    }

    public static SaveLevels LoadData()
    {
      string path = Application.persistentDataPath + "/juego.game";
      if (File.Exists(path))
      {
        BinaryFormatter formatter = new BinaryFormatter();
        FileStream stream = new FileStream(path, FileMode.Open);

        SaveLevels data = formatter.Deserialize(stream) as SaveLevels;

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
