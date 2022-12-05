using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class finishLevel : MonoBehaviour
{
    int total_stars;

    scoreCounter score_fruitStar;
    timeCounter timeStar;

    PlayerDead script2;

    int nLevel;

    public int pointFinishLevel = 100;

    public bool levelDone;

    PauseMenu ss;

    public AudioSource win;

    // Start is called before the first frame update
    void Start()
    {
        total_stars = 0;
        nLevel = SceneManager.GetActiveScene().buildIndex;

        score_fruitStar = GameObject.Find("CountScore").GetComponent<scoreCounter>();

        timeStar = GameObject.Find("CountTime").GetComponent<timeCounter>();

        script2 = GameObject.Find("Player").GetComponent<PlayerDead>();

        levelDone = false;

        ss = GameObject.Find("ControlAndroid").GetComponent<PauseMenu>();

    }

    // Update is called once per frame
    void Update()
    {

    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("Player") && !script2.player_dead && !levelDone)
        {
          levelDone = true;

          if (score_fruitStar.totalFruit > 24) total_stars++;

          score_fruitStar.total_score += pointFinishLevel;
          if (score_fruitStar.total_score >= 900) total_stars++;

          if (timeStar.currentTime > 0) total_stars++;

          if (Levels.levels[nLevel - 1].stars < total_stars)
          {
            Levels.levels[nLevel - 1].stars = total_stars;
          }

          Levels.levels[nLevel].unlocked = true;
          Player pl = GameObject.Find("Playerr").GetComponent<Player>();
          //pl.SavePlayer();
          ss.win = true;
          ss.Pause();
          win.Play();
        }
    }

}
