using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameInstance : MonoBehaviour
{
   public static GameInstance instance_ = null;

    public void Awake()
    {
        if(instance_ == null) { instance_ = this; }
        else
        {
            if(instance_ != this)
            {
                Destroy(gameObject);
            }

        }

        DontDestroyOnLoad(gameObject);
    }


  //  [SerializeField]
  //  private GameObject player_;

    public void ChangeScene(string level)
    {
        Time.timeScale = 1;
        SceneManager.LoadScene(level);
    }
    public void ExitGame()
    {
        Application.Quit();
    }

}
