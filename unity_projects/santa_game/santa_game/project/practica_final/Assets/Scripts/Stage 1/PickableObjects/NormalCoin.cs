using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NormalCoin : MonoBehaviour
{
    float rotation = 3.0f;
    public int puntuation;

    void Update()
    {

        transform.Rotate(0.0f, rotation, 0.0f, Space.World);
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Player")
        {
            other.GetComponent<PuntuationController>().TakePuntuation(puntuation);
            Destroy(gameObject);
        }
    }
}
