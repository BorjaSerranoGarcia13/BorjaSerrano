using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class FinishGame : MonoBehaviour
{
    void Start()
    {
    }

    public void LoadB(int sceneANumber)
    {
        Debug.Log("sceneBuildIndex to load: " + sceneANumber);
        SceneManager.LoadScene(sceneANumber);
    }

    void OnTriggerEnter(Collider col)
    {
        if (col.gameObject.CompareTag("Player")){
            LoadB(0);
        }
    }
}
