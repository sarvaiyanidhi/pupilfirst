[@bs.config {jsx: 3}];
[%bs.raw {|require("./courseShow__LevelSelector.css")|}];

open CourseShow__Types;

let str = React.string;

let levelSelectorClasses = isSelected => {
  let defaultClasses = "course-level__select w-1/2 px-4 py-2 focus:outline-none text-sm font-semibold ";
  defaultClasses ++ (isSelected ? "bg-primary-100 text-primary-500" : "");
};

let updateSelectedLevel =
    (levels, setSelectedLevelId, showLevelZero, setShowLevelZero, event) => {
  let selectedLevelId = ReactEvent.Form.target(event)##value;
  let level =
    levels |> ListUtils.findOpt(l => l |> Level.id == selectedLevelId);

  switch (level) {
  | Some(_) =>
    showLevelZero ? setShowLevelZero(_ => false) : ();
    setSelectedLevelId(_ => selectedLevelId);
  | None => ()
  };
};

let levelName = level =>
  "L"
  ++ (level |> Level.number |> string_of_int)
  ++ ": "
  ++ (level |> Level.name);

[@react.component]
let make =
    (
      ~levels,
      ~selectedLevelId,
      ~setSelectedLevelId,
      ~showLevelZero,
      ~setShowLevelZero,
      ~levelZero,
    ) => {
  let orderedLevels =
    levels |> List.filter(l => l |> Level.number != 0) |> Level.sort;
  let currentLevel =
    levels |> ListUtils.findOpt(l => l |> Level.id == selectedLevelId);
  <div
    className="flex justify-center max-w-sm mx-auto mt-4 rounded-lg overflow-hidden border border-gray-400">
    {
      switch (currentLevel, showLevelZero) {
      | (Some(level), true) =>
        <div
          className="w-1/2 px-4 py-2 focus:outline-none rounded-l-full text-sm font-semibold truncate "
          onClick=(_ => setShowLevelZero(_ => false))>
          {levelName(level) |> str}
        </div>
      | (None, true)
      | (Some(_) | None, false) =>
        <select
          className={levelSelectorClasses(!showLevelZero)}
          onChange={
            updateSelectedLevel(
              orderedLevels,
              setSelectedLevelId,
              showLevelZero,
              setShowLevelZero,
            )
          }
          value=selectedLevelId>
          {
            orderedLevels
            |> List.map(l =>
                 <option value={l |> Level.id} key={l |> Level.id}>
                   {levelName(l) |> str}
                 </option>
               )
            |> Array.of_list
            |> React.array
          }
        </select>
      }
    }
    {
      switch (levelZero) {
      | Some(level) =>
        <button
          className={
            "border-l border-gray-400 font-semibold truncate "
            ++ levelSelectorClasses(showLevelZero)
          }
          onClick=(_e => setShowLevelZero(_ => true))>
          {level |> Level.name |> str}
        </button>
      | None => React.null
      }
    }
  </div>;
};