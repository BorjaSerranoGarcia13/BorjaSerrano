using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

public class MenuAndroid : MonoBehaviour
{
    public void StartGame()
    {
      string path = Application.persistentDataPath + "./juego66.game";
      BinaryFormatter bf = new BinaryFormatter();

    if (File.Exists(path))
      {
        Player pl = GameObject.Find("Playerr").GetComponent<Player>();
        pl.LoadPlayer();
      }


      SceneManager.LoadScene("AllLevels");
    }

    public void OptionsGame()
    {
      SceneManager.LoadScene("Options");
    }

    public void CreditsGame()
    {
      SceneManager.LoadScene("Credits");
    }

    public void ExitGame()
    {
      SceneManager.LoadScene("Instructions");
    }
}
