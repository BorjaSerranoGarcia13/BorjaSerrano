using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class timeCounter : MonoBehaviour
{
    public float currentTime = 0f;
    public float startingTime = 10f;

    float currentTimeCr = 0f;

    public Text countdownText;
    public Text countdownTextCr;
    public Text score1;
    public Text score2;
    public Text guion;

    public Text winner;

    scoreCounter script;

    GameObject finishMenu;
    GameObject pauseMenuUI;
    GameObject cronometroMenu;

    public bool GameIsPaused = true;

    Scene scene;

    public bool crStarts;

    GameObject Player1;
    GameObject Player2;
    GameObject Ball;

    Vector3 player1Pos;
    Vector3 player2Pos;
    Vector3 ballPos;

    // Start is called before the first frame update
    void Start()
    {
      currentTime = startingTime;
      countdownText.color = Color.black;

      script = GameObject.Find("ScoreManager").GetComponent<scoreCounter>();

      finishMenu = GameObject.Find("MatchEnd");
      pauseMenuUI = GameObject.Find("ScoreInGame");
      cronometroMenu = GameObject.Find("Cronometro");
      scene = SceneManager.GetActiveScene();

      pauseMenuUI.SetActive(true);
      finishMenu.SetActive(false);
      cronometroMenu.SetActive(true);
      GameIsPaused = true;

      currentTimeCr = 3f;
      Time.timeScale = 1f;
      crStarts = false;

      Player1 = GameObject.Find("Player1");
      Player2 = GameObject.Find("Player2");
      Ball = GameObject.Find("Ball");

      player1Pos = Player1.transform.position;
      player2Pos = Player2.transform.position;
      ballPos = Ball.transform.position;
    }

    void Update()
    {
      if (GameIsPaused)
      {
        Cronometro();
      }
      else
      {
        Pause();
      }
      countdownText.text = currentTime.ToString("0.0");
    }

    void Pause()
    {
      if (script.movActive)
      {
        if (currentTime > 0) currentTime -= 1 * Time.deltaTime;
        else
        {
          currentTime = 0;
          Time.timeScale = 0f;
          finishMenu.SetActive(true);
          if (script.scorePlayer1 > script.scorePlayer2)
          {
            winner.text = "Player 1 win !!";
          }
          else if (script.scorePlayer1 < script.scorePlayer2)
          {
            winner.text = "Player 2 win !!";
          }
          else
          {
            winner.text = "Both equally bad !!";
          }

        }
      }

    }

    public void Cronometro()
    {
      if (!crStarts)
      {
        currentTimeCr = 3f;
        crStarts = true;
        script.movActive = false;
        Player1.transform.position = player1Pos;
        Player2.transform.position = player2Pos;
        Ball.transform.position = ballPos;
        Ball.transform.parent = null;
        Player1.GetComponent<Rigidbody>().velocity = Vector3.zero;
        Player1.GetComponent<Rigidbody>().angularVelocity = Vector3.zero;
        Player2.GetComponent<Rigidbody>().velocity = Vector3.zero;
        Player2.GetComponent<Rigidbody>().angularVelocity = Vector3.zero;
        Ball.GetComponent<Rigidbody>().velocity = Vector3.zero;
        Ball.GetComponent<Rigidbody>().angularVelocity = Vector3.zero;
      }
      cronometroMenu.SetActive(true);
      countdownTextCr.enabled = true;
      score1.enabled = true;
      score2.enabled = true;
      guion.enabled = true;

      if (currentTimeCr > 0) { currentTimeCr -= 1 * Time.deltaTime; }
      else
      {
        currentTimeCr = 0;
        GameIsPaused = false;
        countdownTextCr.enabled = false;
        score1.enabled = false;
        score2.enabled = false;
        guion.enabled = false;
        cronometroMenu.SetActive(false);
        script.movActive = true;
        crStarts = false;
      }

      countdownTextCr.text = currentTimeCr.ToString("0");
      score1.text = script.scorePlayer1.ToString("0");
      score2.text = script.scorePlayer2.ToString("0");
    }

}
