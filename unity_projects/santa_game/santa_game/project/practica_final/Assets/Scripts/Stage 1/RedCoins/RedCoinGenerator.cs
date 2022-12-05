using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RedCoinGenerator : MonoBehaviour
{
    public bool pressed; 
    public GameObject coin_prefab;
    public Transform[] coin;

    void Start()
    {
        pressed = false;
    }

    private void Update()
    {
       
    }

    private void OnTriggerEnter(Collider other)
    {
        
        if (other.tag == "Player")
        {
            if (!pressed)
            { 
                for (int i = 0; i < coin.Length; i++)
                {
                    Instantiate(coin_prefab, coin[i].transform.position, coin[i].transform.rotation);
                }
                pressed = true;
            } 
        }
    }
}
