using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveMaterials : MonoBehaviour
{
    int ChildrenCounter;
    [SerializeField]
    float scrollSpeed = 0.5F;
    private Renderer []rend;
    // Start is called before the first frame update
    void Start()
    {
        rend = GetComponentsInChildren<Renderer>();
        ChildrenCounter=rend.Length;
    }
    // Update is called once per frame
    void Update()
    {
        float offset = Time.time * scrollSpeed;
        for (int i = 0; i < ChildrenCounter; i++)
        {
            rend[i].material.SetTextureOffset("_MainTex", new Vector2(0, offset));
        }
    }
}
