using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MenuMaps : MonoBehaviour
{
    public void Map1()
    {
      SceneManager.LoadScene(1);
    }

    public void Map2()
    {
      SceneManager.LoadScene(2);
    }

    public void Map3()
    {
      SceneManager.LoadScene(3);
    }
}
