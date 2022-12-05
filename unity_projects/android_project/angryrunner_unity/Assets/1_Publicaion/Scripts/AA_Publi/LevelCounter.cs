using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LevelCounter : MonoBehaviour
{

    public int[] n_stars;


    void Awake()
    {
      DontDestroyOnLoad(this);
    }

    void Start()
    {
      n_stars = new int[11];
      Debug.Log(n_stars[0]);
      n_stars[0] = 1;
      Debug.Log(n_stars[0]);
    }

    // Update is called once per frame
    void Update()
    {
      //Debug.Log(n_stars[0]);
    }
}
