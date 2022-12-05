using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{

    public bool unlocked0;
    public bool unlocked1;
    public bool unlocked2;
    public bool unlocked3;
    public bool unlocked4;
    public bool unlocked5;
    public bool unlocked6;
    public bool unlocked7;
    public bool unlocked8;
    public bool unlocked9;

    public int stars0;
    public int stars1;
    public int stars2;
    public int stars3;
    public int stars4;
    public int stars5;
    public int stars6;
    public int stars7;
    public int stars8;
    public int stars9;

    void Start()
    {

        stars0 =  Levels.levels[0].stars;
        unlocked0 =  Levels.levels[0].unlocked;

        stars1 =  Levels.levels[1].stars;
        unlocked1 =  Levels.levels[1].unlocked;

        stars2 =  Levels.levels[2].stars;
        unlocked2 =  Levels.levels[2].unlocked;

        stars3 =  Levels.levels[3].stars;
        unlocked3 =  Levels.levels[3].unlocked;

        stars4 =  Levels.levels[4].stars;
        unlocked4 =  Levels.levels[4].unlocked;

        stars5 =  Levels.levels[5].stars;
        unlocked5 =  Levels.levels[5].unlocked;

        stars6 =  Levels.levels[6].stars;
        unlocked6 =  Levels.levels[6].unlocked;

        stars7 =  Levels.levels[7].stars;
        unlocked7 =  Levels.levels[7].unlocked;

        stars8 =  Levels.levels[8].stars;
        unlocked8 =  Levels.levels[8].unlocked;

        stars9 =  Levels.levels[9].stars;
        unlocked9 =  Levels.levels[9].unlocked;

      }


    public void SavePlayer()
    {
      stars0 =  Levels.levels[0].stars;
      unlocked0 =  Levels.levels[0].unlocked;

      stars1 =  Levels.levels[1].stars;
      unlocked1 =  Levels.levels[1].unlocked;

      stars2 =  Levels.levels[2].stars;
      unlocked2 =  Levels.levels[2].unlocked;

      stars3 =  Levels.levels[3].stars;
      unlocked3 =  Levels.levels[3].unlocked;

      stars4 =  Levels.levels[4].stars;
      unlocked4 =  Levels.levels[4].unlocked;

      stars5 =  Levels.levels[5].stars;
      unlocked5 =  Levels.levels[5].unlocked;

      stars6 =  Levels.levels[6].stars;
      unlocked6 =  Levels.levels[6].unlocked;

      stars7 =  Levels.levels[7].stars;
      unlocked7 =  Levels.levels[7].unlocked;

      stars8 =  Levels.levels[8].stars;
      unlocked8 =  Levels.levels[8].unlocked;

      stars9 =  Levels.levels[9].stars;
      unlocked9 =  Levels.levels[9].unlocked;


      SaveSystem.SavePlayer(this);
    }

    public void LoadPlayer()
    {
      PlayerData data = SaveSystem.LoadPlayer();


      stars0 =  data.stars0;
      unlocked0 =  data.unlocked0;

      stars1 =  data.stars1;
      unlocked1 =  data.unlocked1;

      stars2 =  data.stars2;
      unlocked2 =  data.unlocked2;

      stars3 =  data.stars3;
      unlocked3 =  data.unlocked3;

      stars4 =  data.stars4;
      unlocked4 =  data.unlocked4;

      stars5 =  data.stars5;
      unlocked5 =  data.unlocked5;

      stars6 =  data.stars6;
      unlocked6 =  data.unlocked6;

      stars7 =  data.stars7;
      unlocked7 =  data.unlocked7;

      stars8 =  data.stars8;
      unlocked8 =  data.unlocked8;

      stars9 =  data.stars9;
      unlocked9 =  data.unlocked9;


      Levels.levels[0].stars =stars0;
        Levels.levels[0].unlocked =unlocked0;
        Debug.Log(Levels.levels[0].stars);
     Levels.levels[1].stars =stars1;
       Levels.levels[1].unlocked =unlocked1;

       Levels.levels[2].stars =stars2;
       Levels.levels[2].unlocked =unlocked2;

        Levels.levels[3].stars =stars3;
      Levels.levels[3].unlocked =unlocked3;

        Levels.levels[4].stars =stars4;
        Levels.levels[4].unlocked =unlocked4;

        Levels.levels[5].stars =stars5;
        Levels.levels[5].unlocked =unlocked5;

       Levels.levels[6].stars =stars6;
        Levels.levels[6].unlocked =unlocked6;

       Levels.levels[7].stars =stars7;
        Levels.levels[7].unlocked =unlocked7;

        Levels.levels[8].stars =stars8;
        Levels.levels[8].unlocked =unlocked8;

        Levels.levels[9].stars =stars9;
        Levels.levels[9].unlocked =unlocked9;

    }

}
