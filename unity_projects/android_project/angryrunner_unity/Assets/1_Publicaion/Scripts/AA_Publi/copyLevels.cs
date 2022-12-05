using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class copyLevels : MonoBehaviour
{
    public struct Level {
      public bool unlocked;
      public int stars;
    }

    public Level[] level = new Level[10];

    // Start is called before the first frame update
    void Start()
    {
      for (int i = 0; i < level.Length; i++)
      {
        level[i].stars =  Levels.levels[i].stars;
        level[i].unlocked =  Levels.levels[i].unlocked;
      }

      //SaveData.SavesData(this);
    }

    // Update is called once per frame
    void Update()
    {

    }
}
