using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;


public class Levels : MonoBehaviour
{
    public struct Level {
      public bool unlocked;
      public int stars;
    }

    public Sprite locked;
    public Sprite unlocked;

    public Sprite stars0;
    public Sprite stars1;
    public Sprite stars2;
    public Sprite stars3;

    public Image[] allLevels;
    public Image[] allStars;

    public Text countdownText;

    public int prueba = 0;

    public int total_stars = 0;

    Banner asas;
    Ads asd;

     //GetComponent<Image>().sprite = dogImg;
    static public Level[] levels = new Level[10];



    // Start is called before the first frame update
    void Start()
    {
      levels[0].unlocked = true;
      asas = GameObject.Find("Banner").GetComponent<Banner>();
      countdownText.color = Color.black;
      asd = GameObject.Find("Ads").GetComponent<Ads>();
      asas.HideBanner();
      asd.PlayInterstitialAd();
    }

    // Update is called once per frame
    void Update()
    {
      asas.HideBanner();
        //levels[PJ_Movement.n_level - 1].stars = PJ_Movement.n_stars;
        total_stars = 0;
        for (int i = 0; i < allLevels.Length; i++)
        {
          if (levels[i].unlocked)
          {
            allLevels[i].sprite = unlocked;
          }
          else
          {
            allLevels[i].sprite = locked;
          }

          switch (levels[i].stars)
          {
            case 0: allStars[i].sprite = stars0; break;
            case 1: allStars[i].sprite = stars1; total_stars += 1;break;
            case 2: allStars[i].sprite = stars2; total_stars += 2;break;
            case 3: allStars[i].sprite = stars3; total_stars += 3;break;
          }

        }

        countdownText.text = total_stars.ToString("0");
    }

    public void Saving()
    {

    }

    public void Level1()
    {
      if (levels[0].unlocked)
      {
        SceneManager.LoadScene("nivel1");
      }
    }

    public void Level2() {
      if (levels[1].unlocked)
      {
        SceneManager.LoadScene("nivel2");
      }
    }

    public void Level3() {
      if (levels[2].unlocked)
      {
        SceneManager.LoadScene("nivel3");
      }
    }

    public void Level4() {
      if (levels[3].unlocked)
      {
        SceneManager.LoadScene("nivel4");
      }
  }

    public void Level5() {
      if (levels[4].unlocked)
      {
        SceneManager.LoadScene("nivel5");
      }
    }

    public void Level6() {
      if (levels[5].unlocked)
      {
        SceneManager.LoadScene("nivel6");
      }
    }

    public void Level7() {
      if (levels[6].unlocked) {
        SceneManager.LoadScene("nivel7");
      }
    }

    public void Level8() {
      if (levels[7].unlocked)
      {
        SceneManager.LoadScene("nivel8");
      }
    }

    public void Level9() {
      if (levels[8].unlocked) {
        SceneManager.LoadScene("nivel9");
      }
    }

    public void Level10() {
      if (levels[9].unlocked) {
        SceneManager.LoadScene("nivel10");
      }
    }

}
