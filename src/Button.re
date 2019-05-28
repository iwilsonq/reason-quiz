type intent =
  | Primary
  | Secondary
  | Link;

let getClassName = intent =>
  switch (intent) {
  | Primary => "bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded focus:outline-none focus:shadow-outline"
  | Secondary => "bg-gray-300 hover:bg-gray-500 text-gray font-bold py-2 px-4 rounded focus:outline-none focus:shadow-outline"
  | Link => "inline-block align-baseline font-bold text-sm text-blue-500 hover:text-blue-800"
  };

[@react.component]
let make = (~title, ~onClick=_e => (), ~intent=Primary, ~type_="button") =>
  <button className={getClassName(intent)} type_ onClick>
    {title |> React.string}
  </button>;