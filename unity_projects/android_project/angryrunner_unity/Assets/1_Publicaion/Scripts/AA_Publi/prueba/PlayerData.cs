using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class PlayerData
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

    public PlayerData(Player player)
    {

      stars0 =  player.stars0;
      unlocked0 =  player.unlocked0;

      stars1 =  player.stars1;
      unlocked1 =  player.unlocked1;

      stars2 =  player.stars2;
      unlocked2 = player.unlocked2;

      stars3 =  player.stars3;
      unlocked3 = player.unlocked3;

      stars4 =  player.stars4;
      unlocked4 = player.unlocked4;

      stars5 =  player.stars5;
      unlocked5 = player.unlocked5;

      stars6 =  player.stars6;
      unlocked6 = player.unlocked6;

      stars7 =  player.stars7;
      unlocked7 = player.unlocked7;

      stars8 =  player.stars8;
      unlocked8 =  player.unlocked8;

      stars9 =  player.stars9;
      unlocked9 =  player.unlocked9;
    }
}
