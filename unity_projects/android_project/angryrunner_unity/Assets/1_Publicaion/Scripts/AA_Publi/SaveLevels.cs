using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class SaveLevels
{

  public struct Level {
    public bool unlocked;
    public int stars;
  }

  public Level[] level;

  public SaveLevels(copyLevels aa)
  {
    //for (int i = 0; i < aa.level.Length; i++)
    //{
      level[0].unlocked = aa.level[0].unlocked;
      //level[i].stars = aa.level[i].stars;
    //}
  }
}
