#include <BreadEngine/core/system.hpp>

#include <BreadEngine/system/render.hpp>
#include <BreadEngine/system/datastore.hpp>

#include <BreadEngine/components/sprite.hpp>
#include <BreadEngine/components/transform.hpp>

#include <iostream>
#include <cmath>
#include <unordered_map>
#include <string>
#include <tuple>

int main(int argc, const char* argv[])
{
  // Definimos los sistemas
  using datastore = typename brd::DataStore<int,float,std::string,bool>;
  using rendersystem = brd::Render;

  //Instanciamos el gestor de sistemas
  brd::core::SystemManager<datastore, rendersystem> system;

  //Obtemenos las referencias a los sistemas
  auto& data = system.GetSystem<datastore>();
  auto& render = system.GetSystem<brd::Render>();

  //Configuramos el datastore
  brd::DataStoreConfiguration dataconf;
  dataconf.saveFile = "config";
  data.Configure(dataconf);

  //Y cargamos los datos
  data.Load();

  //Configuramos el render
  brd::RenderConfiguration rc;
  rc.width = data.Get<int>("width");
  rc.height = data.Get<int>("height");
  rc.title = data.Get<std::string>("title");
  render.Configure(rc);

  //Creamos el contexto
  brd::core::Context ctxt;

  //Creamos una entidad
  auto& ent = ctxt.CreateEntity();

  //Le añadimos el componente de transformación
  ctxt.AddComponent<brd::Transform2D>(ent);

  //Y el componente de sprite
  ctxt.AddComponent<brd::Sprite>(ent);

  //Obtenemos la referencia a todos los componentes transformación del contexto
  auto& transforms = ctxt.GetComponents<brd::Transform2D>();

  //Obtenemos la tupla de posición del primer componente
  auto p = transforms.data[0].Position();

  //Obtenemos las referencias a la x y la y
  auto& x = std::get<0>(p);
  auto& y = std::get<1>(p);

  //Las ponemos a 0
  x = 0; y = 0;

  //Hacemos lo mismo con la escala
  auto s = transforms.data[0].Scale();
  auto& w = std::get<0>(s);
  auto& he = std::get<1>(s);

  //Obtenemos la referencia a los componentes Sprite
  auto& spr = ctxt.GetComponents<brd::Sprite>();

  //Y al primero le asignamos una imagen
  spr.data[0].LoadImg("img.png");

  float tmp {0.0f};

  //////////////////////////////////////////////////////////////////////
    bool run = true;

    do
    {
      tmp -= 0.01;

      x = static_cast<float>(cos(tmp)*0.1);
      y = static_cast<float>(sin(tmp)*0.1);

      w = 1.0 + static_cast<float>(sin(tmp)*0.1);
      he = 1.0 + static_cast<float>(sin(tmp)*0.1);

      render.Update(ctxt);
    }while(!render.ShouldWindowClose());
  //////////////////////////////////////////////////////////////////////

  return 0;
}


#include <BreadEngine/windows_wrapper.h>
