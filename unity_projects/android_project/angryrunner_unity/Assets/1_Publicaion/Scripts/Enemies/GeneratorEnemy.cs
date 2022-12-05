using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GeneratorEnemy : MonoBehaviour
{
    [SerializeField]
    float generate_time = 2;
    [SerializeField]
    GameObject enemy_prefab;

    bool activate_generator = false;

    GameObject enemy_direction;
    // Update is called once per frame
    void Start()
    {
      StartCoroutine(Generator());
    }

    void Update()
    {
      if (!activate_generator)
      {

      }
      else
      {
        StopCoroutine(Generator());
        Instantiate(enemy_prefab, transform.position, transform.rotation);
        StartCoroutine(Generator());
      }
    }
    IEnumerator Generator()
    {
        activate_generator = false;
        yield return new WaitForSeconds(generate_time);
        activate_generator = true;

    }
}
