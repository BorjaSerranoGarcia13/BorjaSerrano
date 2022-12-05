using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PauseMenu : MonoBehaviour
{
     GameObject pauseMenuUI;
     GameObject GameHud;
     GameObject WinM;

     public bool win = false;

     Scene scene;

    public static bool GameIsPaused = false;
    // Start is called before the first frame update
    void Start()
    {
      pauseMenuUI = GameObject.Find("PauseMenu");
      GameHud = GameObject.Find("GameHud");
      WinM = GameObject.Find("WinMenu");

      scene = SceneManager.GetActiveScene();
    }

    // Update is called once per frame
    void Update()
    {
      if (GameIsPaused && !win) {Pause();}
      else if(GameIsPaused && win) {Pause();}
      else {Resume();}
    }

    public void Resume()
    {
      if (win)
      {
        win = false;
        SceneManager.LoadScene("AllLevels");
      }
      pauseMenuUI.SetActive(false);
      WinM.SetActive(false);
      GameHud.SetActive(true);
      Time.timeScale = 1f;
      GameIsPaused = false;
    }

    public void Pause()
    {
      if (!win)
      {
      pauseMenuUI.SetActive(true);
      GameHud.SetActive(false);
      WinM.SetActive(false);
    }
    else {
      pauseMenuUI.SetActive(false);
      GameHud.SetActive(false);
      WinM.SetActive(true);
    }
      Time.timeScale = 0f;
      GameIsPaused = true;
    }

    public void Retry()
    {
      Scene scene = SceneManager.GetActiveScene();
      SceneManager.LoadScene(scene.name);
      win = false;
      Resume();
    }

    public void PauseGame()
    {
      GameIsPaused = true;
    }

    public void PlayGame()
    {
      GameIsPaused = false;
    }

    public void ChooseLevel()
    {
      GameIsPaused = false;
      SceneManager.LoadScene("AllLevels");
    }

    public void GoToMenu()
    {
      GameIsPaused = false;
      SceneManager.LoadScene("Menu");
    }

}
